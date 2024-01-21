/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:18:37 by orezek            #+#    #+#             */
/*   Updated: 2024/01/19 20:32:52 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_read_line(int fd, char **map_str)
{
	char	*tmp_ptr;
	char	*line;

	line = NULL;
	tmp_ptr = NULL;
	line = ft_get_next_line(fd);
	while (line)
	{
		tmp_ptr = *map_str;
		*map_str = ft_strjoin(tmp_ptr, line);
		if (!map_str)
		{
			free(line);
			free(tmp_ptr);
			free(map_str);
			perror("Error: Map lines error\n");
		}
		free(line);
		free(tmp_ptr);
		line = ft_get_next_line(fd);
	}
}

void	ft_resize_assets(t_game_images *game_images, t_elem_size *elem_size)
{
	mlx_resize_image(game_images->player, elem_size->width, elem_size->height);
	mlx_resize_image
		(game_images->collectible, elem_size->width, elem_size->height);
	mlx_resize_image(game_images->wall, elem_size->width, elem_size->height);
	mlx_resize_image(game_images->exit, elem_size->width, elem_size->height);
}

void	ft_get_display_size(t_game_context *game_context)
{
	mlx_get_monitor_size(0, &game_context->game_dimensions->display_size->width,
		&game_context->game_dimensions->display_size->height);
}

void	ft_set_window_size(t_game_context *game_context)
{
	int32_t	width;
	int32_t	height;

	width = 0;
	height = 0;
	width = game_context->game_dimensions->element_size->width
		* game_context->game_dimensions->map_size->width;
	height = game_context->game_dimensions->element_size->height
		*game_context->game_dimensions->map_size->height;
	if (!game_context->mlx)
		exit(1);
	mlx_set_window_size(game_context->mlx, width, height);
}