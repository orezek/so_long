/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:24:31 by aldokezer         #+#    #+#             */
/*   Updated: 2024/01/13 21:22:56 by orezek           ###   ########.fr       */
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

int32_t	main(int32_t argc, const char *argv[])
{
	t_game_context	*game_context;
	char	**map;

	game_context = malloc(sizeof(t_game_context));
	game_context->game_dimensions = malloc(sizeof(t_game_dimensions));
	game_context->game_dimensions->display_size = malloc(sizeof(t_display_size));
	game_context->collectables = malloc(sizeof(t_collectable));
	game_context->player = malloc(sizeof(t_player));
	// malloc
	game_context->map = ft_load_map("./map.ber");
	// malloc
	game_context->game_dimensions->map_size = ft_get_map_size(game_context->map);
	// malloc
	game_context->game_dimensions->element_size = ft_get_image_size(game_context->game_dimensions->map_size);
	// malloc
	game_context->player->player_position = ft_get_player_position(game_context->map);
	// malloc
	game_context->exit_position = ft_get_exit_position(game_context->map);
	// mlx malloc
	mlx = ft_game_init(game_context);
	// malloc
	game_context->game_images = ft_load_graphics(mlx);
	ft_get_display_size(game_context);
	ft_add_graph_elm(mlx, game_context);
	// no malloc only pointer and return is void
	ft_get_no_collectibles(game_context);
	mlx_key_hook(mlx, &on_key_press, (void *) game_context);
	mlx_resize_hook(mlx, &on_window_resize, (void *) game_context);
	mlx_loop(mlx);
	ft_clean_game(mlx, game_context);
	return (EXIT_SUCCESS);
}
