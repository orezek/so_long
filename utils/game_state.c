/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:18:26 by orezek            #+#    #+#             */
/*   Updated: 2024/01/13 21:20:27 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_exit_position	*ft_get_exit_position(char **map)
{
	t_exit_position	*exit_position;

	exit_position = malloc(sizeof(t_player_position));
	if(!exit_position)
		return (NULL);
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'E')
			{
				exit_position->y = y;
				exit_position->x = x;
				return (exit_position);
			}
			x++;
		}
		y++;
	}
	return (NULL);
}

int	ft_end_game(t_game_context *game_context)
{
	extern mlx_t	*mlx;
	if (game_context->player->player_position->x == game_context->exit_position->x &&
		game_context->player->player_position->y == game_context->exit_position->y &&
		game_context->collectables->remaining_collectables == 0)
		{
			ft_printf("%s\n", "Exit Reached");
			mlx_close_window(mlx);
			return (0);
		}
	return(1);
}

t_player_position	*ft_get_player_position(char **map)
{
	t_player_position	*player_position;

	player_position = malloc(sizeof(t_player_position));
	if(!player_position)
		return (NULL);
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'P')
			{
				player_position->y = y;
				player_position->x = x;
				return (player_position);
			}
			x++;
		}
		y++;
	}
	return (NULL);
}