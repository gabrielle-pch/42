/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpochon <gpochon@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:13:05 by gpochon           #+#    #+#             */
/*   Updated: 2024/12/30 15:51:35 by gpochon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

size_t	count_lines(const char *filename, t_g *game)
{
	int		fd;
	size_t	line_count;
	char	*line;

	line_count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	game->height = line_count;
	return (line_count);
}

char	**load_map(const char *filename, t_g *game)
{
	int		fd;
	char	*line;
	char	**map;
	size_t	line_count;
	int		i;

	line_count = count_lines(filename, game);
	if (line_count == 0)
		return (NULL);
	fd = open(filename, O_RDONLY);
	map = malloc(sizeof(char *) * (line_count + 1));
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map[i] = ft_strdup(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void	load_sprites(t_g *game)
{
	int	img_width;
	int	img_height;

	img_height = game->tile_size;
	img_width = game->tile_size;
	game->wall = mlx_xpm_file_to_image(game->mlx, SPRITE_WALL, &img_width,
			&img_height);
	game->floor = mlx_xpm_file_to_image(game->mlx, SPRITE_FLOOR, &img_width,
			&img_height);
	game->mob = mlx_xpm_file_to_image(game->mlx, SPRITE_MOB, &img_width,
			&img_height);
	load_portal(game);
	load_gem(game);
	game->chr = mlx_xpm_file_to_image(game->mlx, SPRITE_STILL, &img_width,
			&img_height);
	if (game->wall == NULL || game->floor == NULL
		|| game->collectible[0] == NULL || game->exit[0] == NULL
		|| game->chr == NULL)
	{
		error_exit(game, "Euh y a un souci avec les textures\n");
	}
}

static void	put_image(t_g *game, int y, int x)
{
	int	px;
	int	py;

	px = x * game->tile_size;
	py = y * game->tile_size;
	if (game->map[y][x] == '1')
		put_img(game, game->wall, px, py);
	else if (game->map[y][x] == '0')
		put_img(game, game->floor, px, py);
	else if (game->map[y][x] == 'C')
		animate_gem(game, px, py);
	else if (game->map[y][x] == 'E')
		animate_portal(game, px, py);
	else if (game->map[y][x] == 'P')
		put_img(game, game->chr, px, py);
	else if (game->map[y][x] == 'M')
		put_img(game, game->mob, px, py);
}

void	render_map(t_g *game)
{
	int	x;
	int	y;

	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			put_image(game, y, x);
		}
	}
}
