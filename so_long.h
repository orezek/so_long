/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:27:03 by aldokezer         #+#    #+#             */
/*   Updated: 2023/12/24 21:26:15 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft/libft.h"
# include "mlx42/include/MLX42/MLX42.h"

typedef struct game_assets_s
{
	mlx_image_t wall;
	mlx_image_t player;
	mlx_image_t	collectible;
	mlx_image_t	exit;
	mlx_image_t	space;

} game_assets_t;

char	**generate_map(void);
void	print_map(char **map);
#endif

