/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:44:47 by orezek            #+#    #+#             */
/*   Updated: 2024/01/22 08:35:24 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_clean_memory(t_game_context *game_context, char *error_str)
{
	ft_free_array(game_context->map->original_map);
	ft_free_array(game_context->map->flooded_map);
	free(game_context->map);
	free(game_context->game_dimensions->display_size);
	free(game_context->game_dimensions);
	free(game_context->player->player_position);
	free(game_context->player);
	free(game_context);
	ft_putstr_fd(error_str, 2);
	exit(1);
}
