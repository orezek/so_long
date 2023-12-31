/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 20:47:57 by orezek            #+#    #+#             */
/*   Updated: 2023/12/31 11:44:47 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
// x is height = collumn y is row
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
			// else if (x == height - 1)
			// 	game_map[x][y] = 'X';
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

void	ft_add_graph_elm(char **map, t_game_assets *game_assets, mlx_t *mlx, t_elem_size elem_size)
{
	int	x;
	int	y;

	y = 0;
	//height from top to buttom
	while (*map)
	{
		x = 0;
		//width = from left to right
		while(**map)
		{
			if (**map == '1')
				mlx_image_to_window(mlx, game_assets->wall, x * elem_size.width, y * elem_size.height);
			// else if (**map == 'P')
			// 	mlx_image_to_window(mlx, game_assets->player, x * elem_size.width, y * elem_size.height);
			// else if (**map == 'E')
			// 	mlx_image_to_window(mlx, game_assets->exit, x * elem_size.width, y * elem_size.height);
			// else if (**map == 'C')
			// 	mlx_image_to_window(mlx, game_assets->collectible, x * elem_size.width, y * elem_size.height);
			(*map)++;
			x++;
		}
		map++;
		y++;
	}
	ft_printf("x: %d\ny: %d\n", x, y);
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

t_elem_size	ft_cal_elem_size(t_map_size *map_size)
{
	t_elem_size 	elem_size;
	t_display_size	*display_size;

	display_size = malloc(sizeof(display_size));
	mlx_get_monitor_size(0, &display_size->width, &display_size->height);
	elem_size.width = (double) display_size->width / map_size->width;
	elem_size.height = (double) display_size->height / map_size->height;
	return (elem_size);
}
// mam velikost displeje x, y
// mam velikost mapy pocet x, y
// potrebuji vypocitat velikost elementu tak abych element x * mapa x == displeje
// dx = 1680 (width), mx 10, ex x, double dx/mx = ex
