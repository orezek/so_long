/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 20:47:57 by orezek            #+#    #+#             */
/*   Updated: 2024/01/22 17:48:06 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_image_to_window(t_game_context *game, int *y, int *x)
{
	t_elem_size	*elm_s;

	elm_s = game->game_dimensions->element_size;
	if (game->map->original_map[*y][*x] == '1')
		mlx_image_to_window(game->mlx, game
			->game_images->wall, *x * elm_s->width, *y * elm_s->height);
	else if (game->map->original_map[*y][*x] == 'P')
		mlx_image_to_window(game->mlx, game
			->game_images->player, *x * elm_s->width, *y * elm_s->height);
	else if (game->map->original_map[*y][*x] == 'E')
		mlx_image_to_window(game->mlx, game
			->game_images->exit, *x * elm_s->width, *y * elm_s->height);
	else if (game->map->original_map[*y][*x] == 'C')
		mlx_image_to_window(game->mlx, game->game_images
			->collectible, *x * elm_s->width, *y * elm_s->height);
}

void	ft_render_game_map(t_game_context *game)
{
	t_elem_size		*elm_s;
	int				x;
	int				y;

	elm_s = game->game_dimensions->element_size;
	mlx_image_to_window(game->mlx, game->game_images->space, 0, 0);
	ft_resize_assets(game->game_images, elm_s);
	y = 0;
	while (y < game->game_dimensions->map_size->height)
	{
		x = 0;
		while (x < game->game_dimensions->map_size->width)
		{
			ft_image_to_window(game, &y, &x);
			x++;
		}
		y++;
	}
}

void	ft_get_map_size(t_game_context *game)
{
	char		**temp_map;
	char		*temp_row;

	temp_map = game->map->original_map;
	game->game_dimensions->map_size = malloc(sizeof(t_map_size));
	if (!game->game_dimensions->map_size)
		exit(1);
	game->game_dimensions->map_size->height = 0;
	game->game_dimensions->map_size->width = 0;
	while (*temp_map)
	{
		if (game->game_dimensions->map_size->height == 0)
		{
			temp_row = *temp_map;
			while (*temp_row++)
				game->game_dimensions->map_size->width++;
		}
		game->game_dimensions->map_size->height++;
		temp_map++;
	}
}

char	**ft_load_map(char *map_path)
{
	int		fd;
	char	*map_str;
	char	**map;

	map_str = malloc(1);
	if (!map_str)
		return (perror("Error: Map str malloc failed\n"), NULL);
	map_str[0] = '\0';
	fd = open(map_path, O_RDONLY, 0444);
	if (fd == -1)
		return (free(map_str), perror("Error: Map reading failed\n"), NULL);
	ft_read_line(fd, &map_str);
	if (map_str[0] == '\n')
	{
		free(map_str);
		close(fd);
		ft_putstr_fd("Error: Invalid map, starts with '\\n'\n", 2);
		exit(1);
	}
	map = ft_split(map_str, '\n');
	free(map_str);
	close(fd);
	return (map);
}

void	ft_count_collectibles(t_game_context *game)
{
	int		x;
	int		y;
	char	**map;

	game->collectables = malloc(sizeof(t_collectable));
	if (!game->collectables)
		exit (1);
	game->collectables->no_collectables = 0;
	game->collectables->remaining_collectables = 0;
	map = game->map->original_map;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'C')
				game->collectables->no_collectables++;
			x++;
		}
		y++;
	}
	game->collectables->remaining_collectables
		= game->collectables->no_collectables;
}
