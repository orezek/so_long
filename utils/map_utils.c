/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:46:40 by orezek            #+#    #+#             */
/*   Updated: 2024/01/17 23:46:23 by orezek           ###   ########.fr       */
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

void	ft_check_map_elements(char **loaded_map, char **flooded_map)
{
	if (!loaded_map && !flooded_map)
	{
		perror("Maps are invalid:");
		exit(1);
	}
	if (ft_map_char_count(loaded_map, 'E') == 1 && ft_map_char_count(flooded_map, 'e') == 1)
		ft_putstr_fd("Exit is reachagle\n", 1);
	else
		ft_putstr_fd("Error, exit is not reachable or is more then one\n", 1);
	if (ft_map_char_count(loaded_map, 'P') == 1 && ft_map_char_count(flooded_map, 'p') == 1)
		ft_putstr_fd("One player found and can reach the exit\n", 1);
	else
		ft_putstr_fd("Missing a player or more then one found\n", 1);
	if (ft_map_char_count(loaded_map, 'C') >= 1 && ft_map_char_count(loaded_map, 'C') == ft_map_char_count(flooded_map, 'c'))
		ft_putstr_fd("Map has valid number of collectibles\n", 1);
	else
		ft_putstr_fd("Error: some collectibles are not reachable or not found at all\n", 1);
}

int32_t	ft_validate_map_dimensions(char **map)
{
	int32_t		ref;
	int32_t		row_counter;
	char		**map_ptr;


	ref = 0;
	row_counter = 0;
	if(!map)
		return (1);
	ref = ft_strlen(map[0]);
	if (ref < 5)
	{
		ft_putstr_fd("Error: Map validation failed. Not enough columns\n", 1);
		exit(1);
	}
	map_ptr = map;
	while (*map_ptr)
	{
		if (ref != ft_strlen(*map_ptr))
		{
			ft_putstr_fd("Error: Map validation failed. Map is not rectangular!\n", 1);
			exit(1);
		}
		row_counter++;
		map_ptr++;
	}
	if (row_counter < 3)
	{
		ft_putstr_fd("Error: Map validation failed. Not enough rows!\n", 1);
		exit(1);
	}
	ft_putstr_fd("Map validation succeeded, map is correctly rectangular.\n", 1);
	return (0);
}

int32_t	ft_is_wall_valid(char **map)
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
				{
					ft_putstr_fd("Error: Map is not closed. Check the map!\n", 2);
					exit (1);
				}
				x++;
			}
		}
		else
		{
			if (map[y][0] != '1'
				|| map[y][ft_strlen(map[y]) - 1] != '1')
			{
				ft_putstr_fd("Error: Map is not closed. Check the map!\n", 2);
				exit (1);
			}
		}
		y++;
	}
	ft_putstr_fd("Map is correctly closed.\n", 1);
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
		return(ft_putstr_fd("Map suffix is correct.\n", 1), 1);
	ft_putstr_fd("Error: Invalid map name! Check the suffix. '*.ber'\n", 2);
	exit(-1);
}


