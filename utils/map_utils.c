/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:46:40 by orezek            #+#    #+#             */
/*   Updated: 2024/01/14 17:41:13 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
char	**ft_map_fload(char **map)
{
	;
}
// checks if the map has X bigger then Y
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


