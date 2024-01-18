/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:52:31 by orezek            #+#    #+#             */
/*   Updated: 2024/01/18 20:10:41 by orezek           ###   ########.fr       */
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

void	ft_handle_w_key_press(t_game_context *game)
{
	game->game_images->player->instances[0].y
		-= (game->game_dimensions->element_size->height);
	game->player->player_position->y -= 1;
	ft_handle_key_press(game);
}

void	ft_handle_s_key_press(t_game_context *game)
{
	game->game_images->player->instances[0].y
		+= (game->game_dimensions->element_size->height);
	game->player->player_position->y += 1;
	ft_handle_key_press(game);
}

void	ft_handle_a_key_press(t_game_context *game)
{
	game->game_images->player->instances[0].x
		-= (game->game_dimensions->element_size->width);
	game->player->player_position->x -= 1;
	ft_handle_key_press(game);
}

void	ft_handle_d_key_press(t_game_context *game)
{
	game->game_images->player->instances[0].x
		+= (game->game_dimensions->element_size->width);
	game->player->player_position->x += 1;
	ft_handle_key_press(game);
}
