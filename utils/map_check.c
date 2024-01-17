/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 20:47:57 by orezek            #+#    #+#             */
/*   Updated: 2024/01/18 00:26:09 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_render_game_map(mlx_t *mlx, t_game_context *game_context)
{
	t_map_size		*map_size;
	t_elem_size		*elem_size;
	t_game_images	*game_images;
	char			**map;
	int				x;
	int				y;

	map = game_context->map->original_map;
	elem_size = game_context->game_dimensions->element_size;
	map_size = game_context->game_dimensions->map_size;
	game_images = game_context->game_images;
	mlx_image_to_window(mlx, game_images->space, 0, 0);
	ft_resize_assets(game_images, game_context->game_dimensions->element_size);
	//height from top to buttom
	y = 0;
	while (y < map_size->height)
	{
		x = 0;
		//width = from left to right
		while(x < map_size->width)
		{
			if (map[y][x] == '1')
				mlx_image_to_window(mlx, game_images->wall, x * elem_size->width, y * elem_size->height);
			else if (map[y][x] == 'P')
				mlx_image_to_window(mlx, game_images->player, x * elem_size->width, y * elem_size->height);
			else if (map[y][x]== 'E')
				mlx_image_to_window(mlx, game_images->exit, x * elem_size->width, y * elem_size->height);
			else if (map[y][x] == 'C')
				mlx_image_to_window(mlx, game_images->collectible, x * elem_size->width, y * elem_size->height);
			x++;
		}
		y++;
	}
}

t_map_size *ft_get_map_size(char **map)
{
	t_map_size	*map_size;
	char		**temp_map;
	char		*temp_row;
	int			x;
	int			y;

	temp_map = map;
	map_size = malloc(sizeof(t_map_size));
	if (!map_size)
		return (NULL);
	y = 0;
	while (*temp_map)
	{
		if (y == 0)
		{
			x = 0;
			temp_row = *temp_map;
			while (*temp_row)
			{
				x++;
				temp_row++;
			}
		}
		y++;
		temp_map++;
	}
	map_size->width = x;
	map_size->height = y;
	return (map_size);
}
// loads the map string into 2d array for further processing
char	**ft_load_map(char *map_path)
{
	int		fd;
	char	*line;
	char	*map_str;
	char	*tmp_ptr;
	char	**map;

	map = NULL;
	line = NULL;
	tmp_ptr = NULL;
	map_str = malloc(1);
	if(!map_str)
		return (perror("Error: Map str malloc failed\n"), NULL);
	map_str[0] = '\0';
	fd = open(map_path, O_RDONLY, 0444);
	if (fd == -1)
		return (free(map_str), ("Error: Map reading failed\n"), NULL);
	while(line = ft_get_next_line(fd))
	{
		tmp_ptr = map_str;
		map_str = ft_strjoin(tmp_ptr, line);
		if (!map_str)
			return (free(line), free(tmp_ptr), perror("Error: Map lines error\n"), NULL);
		free(line);
		free(tmp_ptr);
	}
	map = ft_split(map_str, '\n');
	free(map_str);
	close(fd);
	return (map);
}

size_t	ft_count_collectibles(t_game_context *game_context)
{
	int		x;
	int		y;
	char	**map;

	game_context->collectables = malloc(sizeof(t_collectable));
	if(!game_context->collectables)
		return (1);
	game_context->collectables->no_collectables = 0;
	game_context->collectables->remaining_collectables = 0;
	map = game_context->map->original_map;
	if (!map)
		return (1);
	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'C')
				game_context->collectables->no_collectables++;
			x++;
		}
		y++;
	}
	game_context->collectables->remaining_collectables = game_context->collectables->no_collectables;
	return (0);
}


int	ft_check_collectibles(t_game_context *game_context)
{
	int	x_col;
	int	y_col;
	int	i;

	i = 0;
	while (i < game_context->collectables->no_collectables)
	{
		x_col = game_context->game_images->collectible->instances[i].x;
		y_col = game_context->game_images->collectible->instances[i].y;
		if (x_col == game_context->player->player_position->x * game_context->game_dimensions->element_size->width &&
			y_col == game_context->player->player_position->y * game_context->game_dimensions->element_size->height &&
			game_context->game_images->collectible->instances[i].enabled == 1)
			{
				game_context->game_images->collectible->instances[i].enabled = 0;
				game_context->collectables->remaining_collectables -= 1;
			}
		i++;
	}
	return (0);
}

