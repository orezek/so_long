/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:18:26 by orezek            #+#    #+#             */
/*   Updated: 2024/01/22 17:14:09 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_get_exit_position(t_game_context *game)
{
	int				x;
	int				y;
	t_exit_position	*exit_position;

	exit_position = malloc(sizeof(t_player_position));
	if (!exit_position)
		exit(1);
	y = 0;
	while (game->map->original_map[y] != NULL)
	{
		x = 0;
		while (game->map->original_map[y][x] != '\0')
		{
			if (game->map->original_map[y][x] == 'E')
			{
				exit_position->y = y;
				exit_position->x = x;
				game->exit_position = exit_position;
			}
			x++;
		}
		y++;
	}
}

void	ft_get_player_position(t_game_context *game)
{
	int					x;
	int					y;

	game->player = malloc(sizeof(t_player));
	game->player->player_position = malloc(sizeof(t_player_position));
	if (!game->player || !game->player->player_position)
		exit(1);
	y = 0;
	while (game->map->original_map[y] != NULL)
	{
		x = 0;
		while (game->map->original_map[y][x] != '\0')
		{
			if (game->map->original_map[y][x] == 'P')
			{
				game->player->player_position->y = y;
				game->player->player_position->x = x;
				return ;
			}
			x++;
		}
		y++;
	}
	ft_clean_memory(game, "Error: No player found.\n");
}

int32_t	ft_map_char_count(char **map, char char_to_search)
{
	int		x;
	int		y;
	int		counter;

	counter = 0;
	if (!map)
		return (perror("Error: Empty map:"), -1);
	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == char_to_search)
				counter++;
			x++;
		}
		y++;
	}
	return (counter);
}

int	ft_end_game(t_game_context *game_context)
{
	if (game_context->player->player_position->x
		== game_context->exit_position->x
		&& game_context->player->player_position->y
		== game_context->exit_position->y
		&& game_context->collectables->remaining_collectables == 0)
	{
		ft_printf("%s\n", "Exit Reached");
		mlx_close_window(game_context->mlx);
		return (0);
	}
	return (1);
}

int	ft_check_collectibles(t_game_context *game_context)
{
	int	x_col;
	int	y_col;
	int	i;

	i = 0;
	while (i < game_context->collectables->no_collectables)
	{
		x_col = game_context->game_images->collectible->instances[i].x;
		y_col = game_context->game_images->collectible->instances[i].y;
		if (x_col == game_context->player->player_position->x
			* game_context->game_dimensions->element_size->width
			&& y_col == game_context->player->player_position->y
			* game_context->game_dimensions->element_size->height
			&& game_context->game_images
			->collectible->instances[i].enabled == 1)
		{
			game_context->game_images->collectible->instances[i].enabled = 0;
			game_context->collectables->remaining_collectables -= 1;
		}
		i++;
	}
	return (0);
}
