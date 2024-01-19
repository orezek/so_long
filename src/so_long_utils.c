/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:18:37 by orezek            #+#    #+#             */
/*   Updated: 2024/01/19 20:29:34 by orezek           ###   ########.fr       */
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
