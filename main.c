/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:24:31 by aldokezer         #+#    #+#             */
/*   Updated: 2024/01/09 19:18:30 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// global variable
mlx_t *mlx;

mlx_t	*ft_game_init(t_game_context *game_context)
{
	mlx = mlx_init(1, 1, "SO_LONG", true);
	if (!mlx)
		return (NULL);
	mlx_set_window_size(mlx, game_context->game_dimensions->element_size->width * game_context->game_dimensions->map_size->width,
	game_context->game_dimensions->element_size->height * game_context->game_dimensions->map_size->height);
	mlx_set_window_title(mlx, "Game of Hearts");
	return (mlx);
}

void	ft_clean_game(mlx_t *mlx, t_game_context *game_context)
{
	mlx_close_window(mlx);
	mlx_terminate(mlx);
	free(game_context->game_dimensions->map_size);
	free(game_context->game_dimensions->element_size);
	free(game_context->game_dimensions);
	ft_free_array(game_context->map);
}
/*TODO
1) Check leakege before event handling
2) Implement map check
3) Implement game status flags (player, move, etc)
4) game_context struct
	what it will contain?
	1) map
	2) mlx handler
	3) images (Martin includes textures as well)
	4) sets the image
*/
int32_t	main(int32_t argc, const char *argv[])
{
	t_game_context	*game_context;

	game_context = malloc(sizeof(t_game_context));
	game_context->game_dimensions = malloc(sizeof(t_game_dimensions));
	game_context->game_images = malloc(sizeof(t_game_images));
	game_context->map = ft_load_map("./map.ber");
	game_context->game_dimensions->map_size = ft_get_map_size(game_context->map);
	game_context->game_dimensions->element_size = ft_get_elem_size(game_context->game_dimensions->map_size);
	//game_context->game_images = ft_load_graphics(mlx);;
	mlx = ft_game_init(game_context);
	ft_add_graph_elm(mlx, game_context);
	mlx_key_hook(mlx, &on_key_press, (void *) game_context);
	mlx_resize_hook(mlx, &on_window_resize, (void *) game_context);
	mlx_loop(mlx);
	ft_clean_game(mlx, game_context);
	return (EXIT_SUCCESS);
}
