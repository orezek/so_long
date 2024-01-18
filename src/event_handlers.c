/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:59:47 by orezek            #+#    #+#             */
/*   Updated: 2024/01/18 20:08:47 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	on_esc_press(mlx_key_data_t k_data, void *param)
{
	t_game_context	*game_context;

	game_context = (t_game_context *) param;
	if (k_data.key == MLX_KEY_ESCAPE && k_data.action == MLX_PRESS)
	{
		mlx_close_window(game_context->mlx);
		ft_putstr_fd("Game Exited on ESC Press\n", 1);
	}
}

void	on_wsad_press(mlx_key_data_t k_data, void *param)
{
	t_game_context	*game;

	game = (t_game_context *) param;
	if (k_data.key == MLX_KEY_W && k_data.action == MLX_PRESS
		&& game->map->original_map[game->player->player_position->y -1]
		[game->player->player_position->x] != '1')
		ft_handle_w_key_press(game);
	else if (k_data.key == MLX_KEY_S && k_data.action == MLX_PRESS
		&& game->map->original_map[game->player->player_position->y + 1]
		[game->player->player_position->x] != '1')
		ft_handle_s_key_press(game);
	else if (k_data.key == MLX_KEY_A && k_data.action == MLX_PRESS
		&& game->map->original_map[game->player->player_position->y]
		[game->player->player_position->x - 1] != '1')
		ft_handle_a_key_press(game);
	else if (k_data.key == MLX_KEY_D && k_data.action == MLX_PRESS
		&& game->map->original_map[game->player->player_position->y]
		[game->player->player_position->x + 1] != '1')
		ft_handle_d_key_press(game);
}

void	on_resize(int32_t width, int32_t height, void *param)
{
	ft_printf("Current window size: %d:%d\n", width, height);
}

void	on_key_press(mlx_key_data_t k_data, void *param)
{
	on_esc_press(k_data, param);
	on_wsad_press(k_data, param);
}

void	on_window_resize(int32_t width, int32_t height, void *param)
{
	on_resize(width, height, param);
}
