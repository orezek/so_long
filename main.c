/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:24:31 by aldokezer         #+#    #+#             */
/*   Updated: 2024/01/07 08:09:21 by orezek           ###   ########.fr       */
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
	int32_t	width;
	int32_t	height;

	mlx_t*	mlx; // mlx data structure (window, context, width, height, delta_time)
	//mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	//mlx_set_setting(MLX_MAXIMIZED, 1);
	//mlx_set_setting(MLX_DECORATED, 1);
	//mlx_set_setting(MLX_SETTINGS_MAX, 1);

	if (!(mlx = mlx_init(1,1, "SO_LONG", true))) // window size x,y, title, window resizable
	{
		return(EXIT_FAILURE); //stdlib macro 1
	}
	// gets monitor size
	mlx_get_monitor_size(0, &width, &height);
	// mlx_set_window_size(mlx, width, height);
	mlx_set_window_size(mlx, 1680, 1050);
	game_images = ft_load_graphics(mlx);
	// generate map
	char	**map;
	map = ft_generate_map(20, 15);
	map_size = ft_get_map_size(map);
	
	element_size = ft_cal_elem_size(map_size);
	ft_resize_assets(game_images, element_size);
	mlx_image_to_window(mlx, game_images->space, 0, 0);
	ft_add_graph_elm(map, game_images, mlx, element_size);
	mlx_set_window_title(mlx, "Game of Hearts");
	mlx_loop(mlx); // keeps the window being rendered
	mlx_terminate(mlx); // terminates mlx and cleans up the rosources
	return (EXIT_SUCCESS); // stdlib macro 0
}



