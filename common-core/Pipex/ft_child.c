/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpochon <gpochon@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:06:46 by gpochon           #+#    #+#             */
/*   Updated: 2024/12/30 10:59:34 by gpochon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

static void	ft_execute_command(char **cmd, char **envp)
{
	char	*cmd_path;

	cmd_path = ft_path(cmd[0], envp);
	if (!cmd_path)
	{
		free_cmd(cmd);
		error_handler("Command does not exist");
	}
	execve(cmd_path, cmd, envp);
	free(cmd_path);
	free_cmd(cmd);
	error_handler("Command execution failed");
}

static int	killmyself(char *fuckyou)
{
	while (*fuckyou)
	{
		if (*fuckyou != ' ' && *fuckyou != '\t' && *fuckyou != '\n')
			return (0);
		fuckyou++;
	}
	return (1);
}

void	child_1(int *filefd, char **argv, char **envp)
{
	int		infile_fd;
	char	**cmd1;

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
		error_handler("Error opening input file");
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		error_handler("Dup2 infile_fd failed");
	if (dup2(filefd[1], STDOUT_FILENO) == -1)
		error_handler("Dup2 filefd[1] failed");
	close(filefd[0]);
	close(filefd[1]);
	close(infile_fd);
	if (ft_strlen(argv[2]) == 0 || killmyself(argv[2]) == 1)
		error_handler("No 1st command");
	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1)
		error_handler("ft_split failed");
	ft_execute_command(cmd1, envp);
}

void	parent(int *filefd, char **argv, char **envp)
{
	int		outfile_fd;
	char	**cmd2;

	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile_fd == -1)
		error_handler("Error opening output file");
	if (dup2(filefd[0], STDIN_FILENO) == -1)
		error_handler("Dup2 filefd[0] failed");
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		error_handler("Dup2 outfile_fd failed");
	close(filefd[0]);
	close(filefd[1]);
	close(outfile_fd);
	if (ft_strlen(argv[3]) == 0 || killmyself(argv[3]) == 1)
		error_handler("No 2nd command");
	cmd2 = ft_split(argv[3], ' ');
	if (!cmd2)
		error_handler("ft_split failed");
	ft_execute_command(cmd2, envp);
}
