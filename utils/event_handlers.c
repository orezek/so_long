/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:59:47 by orezek            #+#    #+#             */
/*   Updated: 2024/01/17 22:55:10 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	on_esc_press(mlx_key_data_t k_data, void *param)
{
	extern mlx_t	*mlx;

	if (k_data.key == MLX_KEY_ESCAPE && k_data.action == MLX_PRESS)
	{
		mlx_close_window(mlx);
	}
}

void	on_wsad_press(mlx_key_data_t k_data, void *param)
{
	t_game_context	*game_context;

	game_context = (t_game_context *) param;
	if (k_data.key == MLX_KEY_W && k_data.action == MLX_PRESS && game_context->map->original_map[game_context->player->player_position->y -1][game_context->player->player_position->x] != '1')
	{
		game_context->game_images->player->instances[0].y -= (game_context->game_dimensions->element_size->height);
		game_context->player->player_position->y -= 1;
		game_context->player->player_moves++;
		ft_printf("Player move: %d\n", game_context->player->player_moves);
		ft_is_on_collectible(game_context);
		ft_end_game(game_context);
	}
	else if (k_data.key == MLX_KEY_S && k_data.action == MLX_PRESS && game_context->map->original_map[game_context->player->player_position->y + 1][game_context->player->player_position->x] != '1')
	{
		game_context->game_images->player->instances[0].y += (game_context->game_dimensions->element_size->height);
		game_context->player->player_position->y += 1;
		game_context->player->player_moves++;
		ft_printf("Player move: %d\n", game_context->player->player_moves);
		ft_is_on_collectible(game_context);
		ft_end_game(game_context);
	}
	else if (k_data.key == MLX_KEY_A && k_data.action == MLX_PRESS && game_context->map->original_map[game_context->player->player_position->y][game_context->player->player_position->x - 1] != '1')
	{
		game_context->game_images->player->instances[0].x -= (game_context->game_dimensions->element_size->width);
		game_context->player->player_position->x -= 1;
		game_context->player->player_moves++;
		ft_printf("Player move: %d\n", game_context->player->player_moves);
		ft_is_on_collectible(game_context);
		ft_end_game(game_context);
	}
	else if (k_data.key == MLX_KEY_D && k_data.action == MLX_PRESS && game_context->map->original_map[game_context->player->player_position->y][game_context->player->player_position->x + 1] != '1')
	{
		game_context->game_images->player->instances[0].x += (game_context->game_dimensions->element_size->width);
		game_context->player->player_position->x += 1;
		game_context->player->player_moves++;
		ft_printf("Player move: %d\n", game_context->player->player_moves);
		ft_is_on_collectible(game_context);
		ft_end_game(game_context);
	}
}

// reacts on window resizing - experimental
void	on_resize(int32_t width, int32_t height, void *param)
{
	ft_printf("Current window size: %d:%d\n", width, height);
}

// functions that are used directly in the event handler (hook)
void	on_key_press(mlx_key_data_t k_data, void *param)
{
	on_esc_press(k_data, param);
	on_wsad_press(k_data, param);
}

// test resize event
void	on_window_resize(int32_t width, int32_t height, void *param)
{
	on_resize(width, height, param);
}