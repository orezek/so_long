/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:59:47 by orezek            #+#    #+#             */
/*   Updated: 2024/01/11 21:50:00 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

// on escape press
void	on_esc_press(mlx_key_data_t k_data, void *param)
{
	if (k_data.key == MLX_KEY_ESCAPE && k_data.action == MLX_PRESS)
	{
		extern mlx_t	*mlx;
		ft_printf("%s\n", "ESC Pressed");
		mlx_close_window(mlx);
	}
}

void on_wsad_press(mlx_key_data_t k_data, void *param)
{
	t_game_context	*game_context;

	game_context = (t_game_context *) param;

	if (k_data.key == MLX_KEY_W && k_data.action == MLX_PRESS && game_context->map[game_context->player_position->y -1][game_context->player_position->x] != '1')
	{
		ft_printf("%s", "W: pressed\n");
		game_context->game_images->player->instances[0].y -= (game_context->game_dimensions->element_size->height);
		game_context->player_position->y -= 1;
		ft_printf("Player Pos: x:%d y:%d\n", game_context->player_position->x, game_context->player_position->y);
		ft_printf("%c: \n", game_context->map[game_context->player_position->y - 1][game_context->player_position->x]);
	}
	else if (k_data.key == MLX_KEY_S && k_data.action == MLX_PRESS && game_context->map[game_context->player_position->y + 1][game_context->player_position->x] != '1')
	{
		ft_printf("%s", "S: pressed\n");
		game_context->game_images->player->instances[0].y += (game_context->game_dimensions->element_size->height);
		game_context->player_position->y += 1;
		ft_printf("Player Pos: x:%d y:%d\n", game_context->player_position->x, game_context->player_position->y);
		ft_printf("%c: \n", game_context->map[game_context->player_position->y + 1][game_context->player_position->x]);
	}
	else if (k_data.key == MLX_KEY_A && k_data.action == MLX_PRESS && game_context->map[game_context->player_position->y][game_context->player_position->x - 1] != '1')
	{
		ft_printf("%s", "A: pressed\n");
		game_context->game_images->player->instances[0].x -= (game_context->game_dimensions->element_size->width);
		game_context->player_position->x -= 1;
		ft_printf("Player Pos: x:%d y:%d\n", game_context->player_position->x, game_context->player_position->y);
		ft_printf("%c: \n", game_context->map[game_context->player_position->y][game_context->player_position->x - 1]);
	}
	else if (k_data.key == MLX_KEY_D && k_data.action == MLX_PRESS && game_context->map[game_context->player_position->y][game_context->player_position->x + 1] != '1')
	{
		ft_printf("%s", "D: pressed\n");
		game_context->game_images->player->instances[0].x += (game_context->game_dimensions->element_size->width);
		game_context->player_position->x += 1;
		ft_printf("Player Pos: x:%d y:%d\n", game_context->player_position->x, game_context->player_position->y);
		ft_printf("%c: \n", game_context->map[game_context->player_position->y][game_context->player_position->x + 1]);
	}
}
// reacts on window resizing - experimental
void	on_resize(int32_t width, int32_t height, void *param)
{
	ft_printf("On resize: %d\\%d\n", width, height);

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
