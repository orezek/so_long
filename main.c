/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:24:31 by aldokezer         #+#    #+#             */
/*   Updated: 2023/12/24 22:16:55 by orezek           ###   ########.fr       */
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
	mlx_t*	mlx; // mlx data structure (window, context, width, height, delta_time)
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx_set_setting(MLX_MAXIMIZED, 1);
	mlx_set_setting(MLX_DECORATED, 1);
	mlx_set_setting(MLX_SETTINGS_MAX, 1);

	//to get the size of the window - does not work
	int32_t	width;
	int32_t	height;
	width = 0;
	height = 0;
	mlx_get_monitor_size(0, &width, &height);
	ft_printf("width: %d, height: %d\n", width, height);
	//
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "SO_LONG", true))) // window size x,y, title, window resizable
	{
		return(EXIT_FAILURE); //stdlib macro 1
	}


	// How to create an image form png or any other format and display it on the creen by using MLX?

	// Worfklow -> Load texture by mlx_load_png(const char* path) into a mlx_texture_t object
	// -> Convert the texture obj by mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture) into mlx_image_t obj
	// delete the texture object by void mlx_delete_texture(mlx_texture_t* texture)
	// -> Use some FUNC to display the image on the screen! int32_t mlx_image_to_window(mlx_t* mlx, mlx_image_t* img, int32_t x, int32_t y)



	static mlx_texture_t *texture; // A texture object loaded from a disk
	static mlx_image_t *image; // An image struct/object with an individual buffer that can be rendered.

	mlx_texture_t *texture1;
	mlx_image_t *image1;
	// map generator test
	char	**map;
	map = generate_map();
	print_map(map);

	texture = mlx_load_png("./assets/wall.png");
	texture1 = mlx_load_png("./assets/wall.png");
	image = mlx_texture_to_image(mlx, texture);
	image1 = mlx_texture_to_image(mlx, texture1);
	mlx_resize_image(image, 128, 128);
	mlx_resize_image(image1, 128, 128);

	mlx_delete_texture(texture); // cleanup
	mlx_delete_texture(texture1);
	// mlx_image_to_window(mlx, image, 0, 0);
	// mlx_image_to_window(mlx, image, 0, 64);
	int x;
	int y;
	y = 0;
	while (y < 16)
	{
		x = 0;
		while (x < 16)
			{
				if (y % 2 == 0)
					mlx_image_to_window(mlx, image, y * 64, x * 64);
				else
					mlx_image_to_window(mlx, image1, y * 64, x * 64);
				x++;
			}
		y++;
	}
	ft_printf("%d\n", image->count);
	mlx_loop(mlx); // keeps the window being rendered
	mlx_terminate(mlx); // terminates mlx and cleans up the rosources
	return (EXIT_SUCCESS); // stdlib macro 0
}



