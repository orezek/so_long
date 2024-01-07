/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:24:31 by aldokezer         #+#    #+#             */
/*   Updated: 2024/01/07 09:22:16 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



// gcc main.c mlx42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm -o so_long && ./so_long


int32_t main(int32_t argc, const char* argv[])
{

	t_game_images	*game_images;
	t_elem_size		*element_size;
	t_map_size		*map_size;
	char			**map;
	map = NULL;

	mlx_t*	mlx; // mlx data structure (window, context, width, height, delta_time)

	if (!(mlx = mlx_init(1,1, "SO_LONG", true))) // window size x,y, title, window resizable
	{
		return(EXIT_FAILURE); //stdlib macro 1
	}
	game_images = ft_load_graphics(mlx);
	map = ft_load_map("./map.ber");
	map_size = ft_get_map_size(map);
	ft_printf("%d\n%d\n",map_size->width, map_size->height);
	element_size = ft_cal_elem_size(map_size);
	ft_add_graph_elm(mlx, map);
	mlx_set_window_size(mlx, element_size->width * map_size->width, element_size->height * map_size->height);
	mlx_set_window_title(mlx, "Game of Hearts");
	mlx_loop(mlx); // keeps the window being rendered
	mlx_terminate(mlx); // terminates mlx and cleans up the rosources
	return (EXIT_SUCCESS); // stdlib macro 0
}



