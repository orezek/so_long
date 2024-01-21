/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:46:40 by orezek            #+#    #+#             */
/*   Updated: 2024/01/21 22:24:01 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	ft_map_flood(char	**map_to_flood, size_t y, size_t x)
{
	if (map_to_flood[y][x] == 'c' || map_to_flood[y][x] == 'e'
		|| map_to_flood[y][x] == 'p' || map_to_flood[y][x] == '1'
		|| map_to_flood[y][x] == '2')
		return ;
	if (map_to_flood[y][x] == 'C')
		map_to_flood[y][x] = 'c';
	else if (map_to_flood[y][x] == 'P')
		map_to_flood[y][x] = 'p';
	else if (map_to_flood[y][x] == 'E')
		map_to_flood[y][x] = 'e';
	else if (map_to_flood[y][x] == '0')
		map_to_flood[y][x] = '2';
	ft_map_flood(map_to_flood, y + 1, x);
	ft_map_flood(map_to_flood, y - 1, x);
	ft_map_flood(map_to_flood, y, x + 1);
	ft_map_flood(map_to_flood, y, x - 1);
}

void	ft_verify_game_map(char **loaded_map, char **flooded_map)
{
	if (!loaded_map && !flooded_map)
	{
		perror("Error: Map Validation failed");
		exit(1);
	}
	if (ft_map_char_count(loaded_map, 'E') == 1
		&& ft_map_char_count(flooded_map, 'e') == 1)
		ft_putstr_fd("Success: Single exit is reachable.\n", 1);
	else
		ft_putstr_fd("Error: Exit is either not reachable or missing.\n", 1);
	if (ft_map_char_count(loaded_map, 'P') == 1
		&& ft_map_char_count(flooded_map, 'p') == 1)
		ft_putstr_fd("Success: One player found and can reach the exit.\n", 1);
	else
		ft_putstr_fd("Error: Not valid path to the exit.\n", 1);
	if (ft_map_char_count(loaded_map, 'C') >= 1
		&& ft_map_char_count(loaded_map, 'C')
		== ft_map_char_count(flooded_map, 'c'))
		ft_putstr_fd("Success: All collectibles are valid and reachable.\n", 1);
	else
		ft_putstr_fd("Error: some collectibles are not reachable\n", 1);
}

int32_t	ft_validate_map_dimensions(char **map)
{
	int32_t		ref;
	int32_t		row_counter;
	char		**map_ptr;

	ref = 0;
	row_counter = 0;
	if (!map)
		return (1);
	ref = ft_strlen(map[0]);
	if (ref < 5)
		ft_print_error("Error: Map validation failed. Missing columns\n", map);
	map_ptr = map;
	while (*map_ptr)
	{
		if (ref != ft_strlen(*map_ptr))
			ft_print_error
			("Error: Map validation failed. Map is not rectangular!\n", map);
		row_counter++;
		map_ptr++;
	}
	if (row_counter < 3)
		ft_print_error("Error: Map validation failed. Not enough rows!", map);
	ft_putstr_fd
	("Success: Map validation succeeded, map is correctly rectangular.\n", 1);
	return (0);
}

int32_t	ft_check_map_boundary(char **map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (map[y])
	{
		if (y == 0 || map[y + 1] == NULL)
		{
			x = 0;
			while (map[y][x])
			{
				if (map[y][x] != '1')
					ft_print_error("Error: Map boundary issue.\n", map);
				x++;
			}
		}
		else
		{
			if (map[y][0] != '1' || map[y][ft_strlen(map[y]) - 1] != '1')
				ft_print_error("Error: Map boundary issue.\n", map);
		}
		y++;
	}
	ft_putstr_fd("Success: Map boundaries are properly enclosed.\n", 1);
	return (0);
}

int32_t	ft_check_file_name(char *str)
{
	char	*suffix;
	char	*str_suf;

	suffix = "ber";
	if (!str)
		return (-1);
	str_suf = str + (ft_strlen(str) - ft_strlen(suffix));
	if (ft_strlen(str) <= ft_strlen(suffix))
	{
		ft_putstr_fd("Error: Invalid map name! Check the suffix. '*.ber'\n", 2);
		exit(-1);
	}
	if (ft_strncmp(suffix, str_suf, 3) == 0)
		return (ft_putstr_fd("Success: Map suffix is correct.\n", 1), 1);
	ft_putstr_fd("Error: Invalid map name! Check the suffix. '*.ber'\n", 2);
	exit(-1);
}
