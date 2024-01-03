/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:24:31 by aldokezer         #+#    #+#             */
/*   Updated: 2024/01/03 19:24:45 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



// gcc main.c mlx42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm -o so_long && ./so_long


int32_t main(int32_t argc, const char* argv[])
{
	#define WIDTH 1024
	#define HEIGHT 1024
	t_game_textures	*game_textures;
	t_game_assets	*game_assets;
	t_elem_size		element_size;
	t_map_size		*map_size;
	int32_t	width;
	int32_t	height;

	mlx_t*	mlx; // mlx data structure (window, context, width, height, delta_time)
	//mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	//mlx_set_setting(MLX_MAXIMIZED, 1);
	//mlx_set_setting(MLX_DECORATED, 1);
	//mlx_set_setting(MLX_SETTINGS_MAX, 1);

	if (!(mlx = mlx_init(10, 10, "SO_LONG", true))) // window size x,y, title, window resizable
	{
		return(EXIT_FAILURE); //stdlib macro 1
	}
	// gets monitor size
	mlx_get_monitor_size(0, &width, &height);
	mlx_set_window_size(mlx, width, height);
	ft_putnbr_fd(width, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(height, 1);
	ft_putchar_fd('\n', 1);
	// load png files for the whole game
	game_textures = ft_load_textures();
	// load images from textures
	game_assets = ft_load_images(mlx, game_textures);
	// delete textures
	ft_del_textures(game_textures);

	// map generator test
	char	**map;
	char	**m_map;
	map = ft_generate_map(20, 12);
	//ft_print_map(map);
	//TODO Write func to calculate map sizes
	// map_size->width = 120;
	// map_size->height = 110;
	map_size = ft_get_map_size(map);
	element_size = ft_cal_elem_size(map_size);
	ft_resize_assets(game_assets, element_size.width, element_size.height);
	printf("%f\n", element_size.width);
	printf("%f\n", element_size.height);
	printf("map_size_w: %d\n", map_size->width);
	printf("maps_size_h: %d\n", map_size->height);
	mlx_image_to_window(mlx, game_assets->space, 0, 0);
	ft_add_graph_elm(map, game_assets, mlx, element_size);
	mlx_set_window_title(mlx, "Game of Hearts");
	mlx_loop(mlx); // keeps the window being rendered
	mlx_terminate(mlx); // terminates mlx and cleans up the rosources
	return (EXIT_SUCCESS); // stdlib macro 0
}



