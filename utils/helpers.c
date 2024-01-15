/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:31:52 by orezek            #+#    #+#             */
/*   Updated: 2024/01/15 13:31:39 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_free_array(char **array)
{
	char	**tmp_ptr;

	tmp_ptr = array;
	while (*array != NULL)
	{
		free(*array);
		array++;
	}
	free(tmp_ptr);
	return (0);
}

void	ft_get_display_size(t_game_context *game_context)
{
	mlx_get_monitor_size(0, &game_context->game_dimensions->display_size->width,
		&game_context->game_dimensions->display_size->height);
}

void	ft_clean_game(mlx_t *mlx, t_game_context *game_context)
{
	mlx_terminate(mlx);
	free(game_context->game_dimensions->map_size);
	free(game_context->game_dimensions->element_size);
	free(game_context->game_images);
	free(game_context->exit_position);
	free(game_context->player->player_position);
	free(game_context->player);
	free(game_context->collectables);
	free(game_context->game_dimensions->display_size);
	free(game_context->game_dimensions);
	ft_free_array(game_context->map->original_map);
	ft_free_array(game_context->map->flooded_map);
	free(game_context->map);
	free(game_context);
}

void	ft_print_map(char **map)
{
	char	**tmp_ptr;

	tmp_ptr = map;
	while (*tmp_ptr)
	{
		while(**tmp_ptr)
		{
			ft_printf("%c", **tmp_ptr);
			(*tmp_ptr)++;
		}
		tmp_ptr++;
		ft_putchar_fd('\n', 1);
	}
}
