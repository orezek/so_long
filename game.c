/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:24:31 by aldokezer         #+#    #+#             */
/*   Updated: 2024/01/17 23:53:35 by orezek           ###   ########.fr       */
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
	extern mlx_t	*mlx;
	int				width;
	int				height;

	width = game_context->game_dimensions->element_size->width * game_context->game_dimensions->map_size->width;
	height = game_context->game_dimensions->element_size->height * game_context->game_dimensions->map_size->height;
	mlx = mlx_init(width, height, "Game of Hearts", true);
	if (!mlx)
		return (NULL);
	return (mlx);
}

void	ft_clean_game(mlx_t *mlx, t_game_context *game_context)
{
	mlx_close_window(mlx);
	mlx_terminate(mlx);
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
	free(game_context->game_images);
	free(game_context->map);
	free(game_context);
}

void	ft_check_program_arguments(int32_t argct, const char *argvt[])
{
	int		fd;
	char	*buf;

	if (argct == 1)
	{
		ft_putstr_fd("Error: Add valid map to the game! Format *.ber or use default map 'maps/map.ber'!\n", 2);
		exit(1);
	}
	else if(argct > 2)
	{
		ft_putstr_fd("Error:To many arguments provided! Add only valid map path!\n", 2);
		exit(1);
	}
	else if(argct == 2)
	{

		fd = open(argvt[1], O_RDONLY, 0444);
		if (fd == -1)
		{
			perror("Error: File name or path is not valid!\n");
			close(fd);
			exit(1);
		}

		if (read(fd, buf, 1) == 0)
		{
			ft_putstr_fd("Error: File is empty. Check the file!\n", 2);
			close(fd);
			exit(1);
		}
		close(fd);
	}
}

int32_t	main(int32_t argc, const char *argv[])
{
	t_game_context	*game_context;
	extern mlx_t	*mlx;
	char			**map;

	ft_check_program_arguments(argc, argv);
	ft_check_file_name((char *)argv[1]);
	map = ft_load_map((char *)argv[1]);
	game_context = malloc(sizeof(t_game_context));
	game_context->map = malloc(sizeof(t_map));
	game_context->map->original_map = map;
	ft_validate_map_dimensions(game_context->map->original_map);
	ft_is_wall_valid(game_context->map->original_map);
	ft_duplicate_map(game_context);
	game_context->player = malloc(sizeof(t_player));
	game_context->player->player_position = ft_get_player_position(game_context->map->original_map);
	ft_map_flood(game_context->map->flooded_map, game_context->player->player_position->y, game_context->player->player_position->x);
	ft_check_map_elements(game_context->map->original_map, game_context->map->flooded_map);
	game_context->player->player_moves = 0;
	game_context->exit_position = ft_get_exit_position(game_context->map->original_map);
	game_context->game_dimensions = malloc(sizeof(t_game_dimensions));
	game_context->game_dimensions->display_size = malloc(sizeof(t_display_size));
	ft_get_display_size(game_context);
	game_context->game_dimensions->map_size = ft_get_map_size(game_context->map->original_map);
	game_context->game_dimensions->element_size = ft_get_element_size(game_context->game_dimensions->map_size);
	ft_get_no_collectibles(game_context);
	mlx = ft_game_init(game_context);
	game_context->game_images = ft_load_graphics(mlx);
	ft_add_graph_elm(mlx, game_context);
	mlx_key_hook(mlx, &on_key_press, (void *) game_context);
	mlx_resize_hook(mlx, &on_window_resize, (void *) game_context);
	mlx_loop(mlx);
	ft_clean_game(mlx, game_context);
	return (EXIT_SUCCESS);
}

