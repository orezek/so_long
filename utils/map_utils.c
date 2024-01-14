/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:46:40 by orezek            #+#    #+#             */
/*   Updated: 2024/01/14 21:37:35 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

/*
Todo:
1) Map check
2) Restructuing
3) Memory deallocation
4) Norm
END
Maybe iimplement two features
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
7) Map is rectangular
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
void	ft_array_dup(t_game_context *game_context)
{
	char	**map_dup;
	char	**map;
	size_t	counter;
	map = game_context->map->original_map;

	counter = 0;
	while (!map[counter])
		counter++;
	map_dup = malloc(sizeof(char *) * counter + 1);
	if(!map_dup)
		return (NULL);
	counter = 0;
	while(!map[counter])
		map_dup[counter] = ft_strdup(map[counter]);
	map_dup[counter] = NULL;
	game_context->map->flooded_map = map_dup;
}

void	ft_map_flood(t_game_context *game_context, size_t y, size_t x)
{
	char	**map_array = game_context->map;

	if (map_array[y][x] == 'c' || map_array[y][x] == 'e'
		|| map_array[y][x] == 'p' || map_array[y][x] == '1'
		|| map_array[y][x] == '2')
		return ;
	if (map_array[y][x] == 'C')
		map_array[y][x] = 'c';
	else if (map_array[y][x] == 'P')
		map_array[y][x] = 'p';
	else if (map_array[y][x] == 'E')
		map_array[y][x] = 'e';
	else if (map_array[y][x] == '0')
		map_array[y][x] = '2';
	ft_map_flood(map_array, game_context->player->player_position.y + 1, x);
	ft_map_flood(map_array, y - 1, x);
	ft_map_flood(map_array, y, x + 1);
	ft_map_flood(map_array, y, x - 1);
}

void	map_flood_fill(char **map_array, size_t y, size_t x)
{
	if (map_array[y][x] == 'c' || map_array[y][x] == 'e'
		|| map_array[y][x] == 'p' || map_array[y][x] == '1'
		|| map_array[y][x] == '2')
		return ;
	if (map_array[y][x] == 'C')
		map_array[y][x] = 'c';
	else if (map_array[y][x] == 'P')
		map_array[y][x] = 'p';
	else if (map_array[y][x] == 'E')
		map_array[y][x] = 'e';
	else if (map_array[y][x] == '0')
		map_array[y][x] = '2';
	map_flood_fill(map_array, y + 1, x);
	map_flood_fill(map_array, y - 1, x);
	map_flood_fill(map_array, y, x + 1);
	map_flood_fill(map_array, y, x - 1);
}
// checks if the map has X bigger then Y - look at Martin's solution
int32_t	ft_is_map_rectangular(char **map)
{
	;
}
// compares map chars between the original and floaded. This will check of the game is playable
// if collectibles do not match the exit will never open becuase one can safely assume that the collectbiles are behind the wall
// exit must be 1
// player must be 1
void	ft_check_map_elements(char **loaded_map, char **floaded_map)
{
	;
}
// Is the map sorouded by walls (1)?
int32_t ft_is_wall_valid(char **map)
{
	;
}


