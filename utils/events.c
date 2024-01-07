/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:59:47 by orezek            #+#    #+#             */
/*   Updated: 2024/01/07 19:11:43 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	events(mlx_key_data_t k_data, void *param)
{
	if (k_data.key == MLX_KEY_ESCAPE && k_data.action == MLX_PRESS)
	{
		ft_printf("%s", "ESC Pressed.");
	}
}
