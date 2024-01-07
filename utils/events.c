/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:59:47 by orezek            #+#    #+#             */
/*   Updated: 2024/01/07 20:58:52 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
// think about naming these events - is does not make it right, it is not a flag
void	is_esc_event(mlx_key_data_t k_data, void *param)
{
	if (k_data.key == MLX_KEY_ESCAPE && k_data.action == MLX_PRESS)
	{
		ft_printf("%s", "ESC Pressed.");
	}
}
// test resize event
void	is_resized(int32_t width, int32_t height, void *param)
{
	ft_printf("%d\\%d\n", width, height);
}

void	events(mlx_key_data_t k_data, void *param)
{
	is_esc_event(k_data, param);
}
// test resize event
void	win_events(int32_t width, int32_t height, void *param)
{
	is_resized(width, height, param);
}
