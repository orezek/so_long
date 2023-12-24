/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 20:47:57 by orezek            #+#    #+#             */
/*   Updated: 2023/12/24 22:43:59 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	**generate_map(void)
{
	int		height;
	int 	width;
	char	**game_map;
	int		x;
	int		y;

	height = 8;
	width = 8;
	game_map = malloc((height + 1) * sizeof(char*));
	if (!game_map)
		return (NULL);

	y = 0;
	while (y < height)
	{
		x = 0;
		game_map[y] = malloc((width + 1) * sizeof(char));
		while (x < width)
		{
			game_map[y][x] = '1';
			x++;
		}
		game_map[y][x] = '\0';
		y++;
	}
	*(game_map + y) = '\0';
	return (game_map);
}


void	print_map(char **map)
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
// this one iterates over an array by reference (pointer)
// however, I need to par actual coordinates with the array index and then check the value
// in the array. The array will be only abstruction (map) of the screen (window/mlx_image object)
void	add_graphic_elements(char **map)
{
	while (*map)
	{
		while(**map)
		{
			if (**map == '1')
				//mlx_image_to_window(mlx, image, y * 64, x * 64);
			(*map)++;
		}
		map++;
		ft_putchar_fd('\n', 1);
	}
}
