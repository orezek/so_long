/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:31:52 by orezek            #+#    #+#             */
/*   Updated: 2024/01/17 23:12:36 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_free_array(char **array)
{
	char	**tmp_ptr;

	if (!array)
		return (1);
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

void	*ft_duplicate_map(t_game_context *game_context)
{
	char	**map_dup;
	char	**map;
	size_t	counter;
	map = game_context->map->original_map;

	counter = 0;
	while (map[counter] != NULL)
		counter++;
	map_dup = malloc(sizeof(char *) * (counter + 1));
	if(!map_dup)
		return (NULL);
	counter = 0;
	while(map[counter] != NULL)
	{
		map_dup[counter] = ft_strdup(map[counter]);
		counter++;
	}
	map_dup[counter] = NULL;
	game_context->map->flooded_map = map_dup;
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
