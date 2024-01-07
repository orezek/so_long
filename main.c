/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:24:31 by aldokezer         #+#    #+#             */
/*   Updated: 2024/01/07 10:58:03 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

mlx_t	*ft_game_init(char **map)
{
	mlx_t			*mlx;
	t_elem_size		*element_size;
	t_map_size		*map_size;

	map_size = ft_get_map_size(map);
	element_size = ft_get_elem_size(map_size);
	mlx = mlx_init(1, 1, "SO_LONG", true);
	if (!mlx)
		return (NULL);
	mlx_set_window_size(mlx, element_size->width * map_size->width,
		element_size->height * map_size->height);
	mlx_set_window_title(mlx, "Game of Hearts");
	return (mlx);
}

int32_t	main(int32_t argc, const char *argv[])
{
	mlx_t			*mlx;
	char			**map;

	map = NULL;
	map = ft_load_map("./map.ber");
	mlx = ft_game_init(map);
	ft_add_graph_elm(mlx, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
