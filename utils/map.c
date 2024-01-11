/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 20:47:57 by orezek            #+#    #+#             */
/*   Updated: 2024/01/11 09:59:06 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	**ft_generate_map(int width, int height)
{
	char	**game_map;
	int		x;
	int		y;

	game_map = malloc((height + 1) * sizeof(char*));
	if (!game_map)
		return (NULL);

	x = 0;
	while (x < height)
	{
		y = 0;
		game_map[x] = malloc((width + 1) * sizeof(char));
		while (y < width)
		{
			if (x == 2 && y == 2)
				game_map[x][y] = 'P';
			else if (x == 4 && y == 6)
				game_map[x][y] = 'E';
			else if (y == 6 && x == 10 || y == 6 && x == 13 || y == 6 && x == 1)
				game_map[x][y] = 'C';
			else if (y == 0 || y < width && x < 1 || x < height && y == width - 1 || x == height - 1)
				game_map[x][y] = '1';
			else
				game_map[x][y] = '0';
			y++;
		}
		game_map[x][y] = '\0';
		x++;
	}
	*(game_map + x) = '\0';
	return (game_map);
}

void	ft_add_graph_elm(mlx_t *mlx, t_game_context *game_context)
{
	t_map_size		*map_size;
	t_elem_size		*elem_size;
	t_game_images	*game_images;
	char			**map;
	int				x;
	int				y;

	map = game_context->map;
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

void	ft_print_map(char **map)
{
	while (*map)
	{
		while(**map)
		{
			ft_printf("%c", **map);
			(*map)++;
		}
		map++;
		ft_putchar_fd('\n', 1);
	}
}

// element_width = display_width / map_width
// element_width = display_width / map_width

// display_width = element_width * map_width
// display_height = element_height * map_height
t_elem_size	*ft_get_elem_size(t_map_size *map_size)
{
	t_elem_size 	*elem_size;
	t_display_size	*display_size;

	display_size = malloc(sizeof(t_display_size));
	elem_size = malloc(sizeof(t_elem_size));
	mlx_get_monitor_size(0, &display_size->width, &display_size->height);
	elem_size->width =  1620/ map_size->width;
	elem_size->height = 990 / map_size->height;
	printf("ft_get_elem_size: %d:%d\n", elem_size->width, elem_size->height);
	free(display_size);
	return (elem_size);
}

// experimental
t_elem_size	*ft_get_elem_size_v2(t_map_size *map_size, t_display_size *display_size)
{
	t_elem_size 	*elem_size;

	elem_size = malloc(sizeof(t_elem_size));
	elem_size->width =  display_size->width / map_size->width;
	elem_size->height = display_size->height / map_size->height;
	printf("ft_get_elem_size: %d:%d\n", elem_size->width, elem_size->height);
	return (elem_size);
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
	map_str = malloc(sizeof(char *));
	map_str[0] = '\0';
	if(!map_str)
		return (perror("Map str malloc failed"), NULL);
	fd = open(map_path, O_RDONLY, 0444);
	if (fd == -1)
		return (perror("Map reading failed"), NULL);
	while(line = ft_get_next_line(fd))
	{
		tmp_ptr = map_str;
		map_str = ft_strjoin(tmp_ptr, line);
		if (!map_str)
			return (free(line), free(tmp_ptr), perror("Map lines error"), NULL);
		free(line);
		free(tmp_ptr);
	}
	map = ft_split(map_str, '\n');
	free(map_str);
	close(fd);
	return (map);
}

