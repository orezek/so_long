/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:24:31 by aldokezer         #+#    #+#             */
/*   Updated: 2024/01/21 08:40:10 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void	ft_game_init(t_game_context *game_context)
{
	mlx_t	*mlx;

	mlx = mlx_init(1, 1, "Game of Hearts", true);
	if (!mlx)
		exit(1);
	game_context->mlx = mlx;
}

// void	ft_map_init(int32)

int32_t	main(int32_t argc, const char *argv[])
{
	t_game_context	*game_context;
	char			**map;

	ft_check_program_arguments(argc, argv);
	ft_check_file_name((char *)argv[1]);
	map = ft_load_map((char *)argv[1]);
	game_context = malloc(sizeof(t_game_context));
	game_context->map = malloc(sizeof(t_map));
	game_context->map->original_map = map;
	ft_validate_map_dimensions(game_context->map->original_map);
	ft_check_map_boundary(game_context->map->original_map);
	ft_duplicate_map(game_context);
	game_context->player = malloc(sizeof(t_player));
	ft_get_player_position(game_context);
	ft_map_flood(game_context->map->flooded_map, game_context->player->player_position->y, game_context->player->player_position->x);
	ft_verify_game_map(game_context->map->original_map, game_context->map->flooded_map);
	game_context->player->player_moves = 0;
	game_context->exit_position = ft_get_exit_position(game_context->map->original_map);
	game_context->game_dimensions = malloc(sizeof(t_game_dimensions));
	game_context->game_dimensions->display_size = malloc(sizeof(t_display_size));
	ft_get_map_size(game_context);
	ft_count_collectibles(game_context);
	ft_game_init(game_context);
	ft_get_display_size(game_context);
	ft_set_elem_size(game_context);
	ft_set_window_size(game_context);
	game_context->game_images = ft_load_graphics(game_context->mlx);
	ft_render_game_map(game_context);
	mlx_key_hook(game_context->mlx, &on_key_press, (void *) game_context);
	mlx_resize_hook(game_context->mlx, &on_window_resize, (void *) game_context);
	mlx_loop(game_context->mlx);
	ft_release_game_resources(game_context);
	return (EXIT_SUCCESS);
}
