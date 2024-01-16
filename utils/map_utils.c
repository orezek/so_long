/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:46:40 by orezek            #+#    #+#             */
/*   Updated: 2024/01/16 15:49:14 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/*
Todo:
1) Map checks
2) Restructuing
3) Memory deallocation
4) Norm
END
Maybe implement two features
1) Display move count
2) Add Gargamel
*/


/*
Check:
1) Walls are around the map
2) One player
3) One exit
4) At least one collectible
5) Player can reach to Exit
6) All collectibles are reachable by the player
7) Map is rectangular and valid
8) Check map suffix
---------------------
I have:
1) Load map to an array
2) Get map size X and Y
3) Player and Exit coordiantes to start the flood
4) Get number of collectibles

I need some universal character count of the map. To compare between the orginal and floaded map
*/
// creates a duplicate array and moves one coordinate at a time and marks it, the starting position is the player position or the exit position
// it will mark everthing except wall - it cannot pass the walls

/*
How to use this?

I load a map, then I get a player position? How, I have game_context. Use that!
What then? I need a array duplicate to run the fload on. Should I keep a pointer in the game_context?
Oh, yes. So I need function array dup
*/

// free game_context->map-
// free game_context->map->flooded_map
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
// flood the duplicaed map with error checking characters
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

int32_t	ft_get_no_map_elements(char **map, char char_to_search)
{
	int		x;
	int		y;
	int		counter;

	counter = 0;
	if (!map)
		return (perror("Empty map:"), -1);
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

void	ft_check_map_elements(char **loaded_map, char **flooded_map)
{
	if (!loaded_map && !flooded_map)
		perror("Maps are invalid:");
	if (ft_get_no_map_elements(loaded_map, 'E') == 1 && ft_get_no_map_elements(flooded_map, 'e') == 1)
	{
		ft_putstr_fd("Exit is reachagle\n", 1);
	}
	else
	{
		ft_putstr_fd("Error, exit is not reachable or is more then one\n", 1);
	}
	if (ft_get_no_map_elements(loaded_map, 'P') == 1 && ft_get_no_map_elements(flooded_map, 'p') == 1)
	{
		ft_putstr_fd("One player found and can reach the exit\n", 1);
	}
	else
	{
		ft_putstr_fd("Missing a player or more then one found\n", 1);
	}
	if (ft_get_no_map_elements(loaded_map, 'C') >= 1 && ft_get_no_map_elements(loaded_map, 'C') == ft_get_no_map_elements(flooded_map, 'c'))
	{
		ft_putstr_fd("Map has valid number of collectibles\n", 1);
	}
	else
	{
		ft_putstr_fd("Error: some collectibles are not reachable or not found at all\n", 1);
	}
}

// checks if the map has X bigger then Y - look at Martin's solution
int32_t	ft_is_map_rectangular(char **map)
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
		ft_putstr_fd("Error: Invalid map. Not enough columns\n", 1);
		exit(1);
	}
	map_ptr = map;
	while (*map_ptr)
	{
		if (ref != ft_strlen(*map_ptr))
		{
			ft_putstr_fd("Error: Invalid map. Map is not rectangular!\n", 1);
			exit(1);
		}
		row_counter++;
		map_ptr++;
	}
	if (row_counter < 3)
	{
		ft_putstr_fd("Error: Invalid map. Not enough rows!\n", 1);
		exit(1);
	}
	return (0);
}

// Is the map sorouded by walls (1)?
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

// Check the validity of a map suffix
int32_t	ft_check_valid_suffix(char *str)
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


