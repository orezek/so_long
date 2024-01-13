/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:31:52 by orezek            #+#    #+#             */
/*   Updated: 2024/01/13 20:51:57 by orezek           ###   ########.fr       */
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
