/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpochon <gpochon@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:52:47 by gpochon           #+#    #+#             */
/*   Updated: 2024/12/30 10:58:33 by gpochon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	error_handler(const char *name)
{
	if (errno == 0)
		errno = EINVAL;
	perror(name);
	exit(EXIT_FAILURE);
}
