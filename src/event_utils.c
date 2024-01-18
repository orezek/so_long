/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:52:31 by orezek            #+#    #+#             */
/*   Updated: 2024/01/18 19:52:49 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_handle_key_press(t_game_context *game)
{
	game->player->player_moves++;
	ft_printf("Player move: %d\n", game->player->player_moves);
	ft_check_collectibles(game);
	ft_end_game(game);
}
