/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:59:47 by orezek            #+#    #+#             */
/*   Updated: 2024/01/08 22:24:38 by orezek           ###   ########.fr       */
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
	if (k_data.key == MLX_KEY_W && k_data.action == MLX_PRESS)
		ft_printf("%s", "W: pressed\n");
	else if (k_data.key == MLX_KEY_S && k_data.action == MLX_PRESS)
		ft_printf("%s", "S: pressed\n");
	else if (k_data.key == MLX_KEY_A && k_data.action == MLX_PRESS)
		ft_printf("%s", "A: pressed\n");
	else if (k_data.key == MLX_KEY_D && k_data.action == MLX_PRESS)
		ft_printf("%s", "D: pressed\n");
}
// reacts on window resizing
void	on_resize(int32_t width, int32_t height, void *param)
{
	// this is just test - think about how to work with struct of structs
	int t_height = 100;
	int	t_width = 100;
	// t_game_context	*game_context;
	// game_context = (t_game_context*) param;
	// game_context->game_dimensions = malloc(sizeof(t_game_dimensions));
	// game_context->game_dimensions->display_size->width = width;
	// game_context->game_dimensions->display_size->height = height;
	// t_height = game_context->game_dimensions->display_size->height;
	// t_width = game_context->game_dimensions->display_size->width;
	ft_printf("%d\\%d\n", t_width, t_height);
}

// functions that are used directly in the event handler
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
