/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:24:31 by aldokezer         #+#    #+#             */
/*   Updated: 2024/01/16 15:52:10 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// global variable
mlx_t	*mlx;

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
	free(game_context->player->player_position);
	free(game_context->player);
	free(game_context->exit_position);
	ft_free_array(game_context->map->original_map);
	ft_free_array(game_context->map->flooded_map);
	free(game_context->game_dimensions->display_size);
	free(game_context->game_dimensions->map_size);
	free(game_context->game_dimensions->element_size);
	free(game_context->game_dimensions);
	free(game_context->collectables);
	free(game_context->map);
	free(game_context);
}

void	ft_check_program_arguments(int32_t argct, const char *argvt[])
{
	if (argct == 1)
	{
		ft_putstr_fd("Error: Add valid map to the game! Format *.ber or use default map 'map.ber'\n", 2);
		exit(1);
	}
	else if(argct > 2)
	{
		ft_putstr_fd("Error:To many arguments provided! Add only valid map path!\n", 2);
		exit(1);
	}
}

int32_t	main(int32_t argc, const char *argv[])
{
	t_game_context	*game_context;
	char			**map;

	ft_check_program_arguments(argc, argv);
	ft_check_valid_suffix((char *)argv[1]);
	// to here no malloc()
	map = ft_load_map((char *)argv[1]); // malloc
	game_context = malloc(sizeof(t_game_context)); // malloc
	game_context->map = malloc(sizeof(t_map)); // malloc
	game_context->map->original_map = map; // no malloc only reference
	ft_is_map_rectangular(game_context->map->original_map); // no malloc
	ft_is_wall_valid(game_context->map->original_map); // na malloc
	ft_duplicate_map(game_context); // malloc
	ft_check_map_elements(game_context->map->original_map, game_context->map->flooded_map); // no malloc
	game_context->player = malloc(sizeof(t_player)); // malloc
	game_context->player->player_position = ft_get_player_position(game_context->map->original_map); // malloc
	game_context->player->player_moves = 0; // no malloc
	game_context->exit_position = ft_get_exit_position(game_context->map->original_map); // malloc
	ft_map_flood(game_context->map->flooded_map, game_context->player->player_position->y, game_context->player->player_position->x); // no malloc
	game_context->game_dimensions = malloc(sizeof(t_game_dimensions));
	game_context->game_dimensions->display_size = malloc(sizeof(t_display_size));
	ft_get_display_size(game_context); // wrapper around a mlx_get_display_size
	game_context->game_dimensions->map_size = ft_get_map_size(game_context->map->original_map); // map size
	game_context->game_dimensions->element_size = ft_get_image_size(game_context->game_dimensions->map_size); // gets the element size to construct the game graphics
	ft_get_no_collectibles(game_context); // gets number of collectibles
	//up to here no memory leaks
	mlx = ft_game_init(game_context); // creates a window and displays it
	game_context->game_images = ft_load_graphics(mlx); // loads graphics to the game struct
	ft_add_graph_elm(mlx, game_context); // draws images on the window
	// allocates the memory and initialize values
	mlx_key_hook(mlx, &on_key_press, (void *) game_context);
	mlx_resize_hook(mlx, &on_window_resize, (void *) game_context);
	mlx_loop(mlx);
	ft_clean_game(mlx, game_context);
	return (EXIT_SUCCESS);
}
