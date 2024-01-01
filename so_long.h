/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:27:03 by aldokezer         #+#    #+#             */
/*   Updated: 2023/12/31 16:04:32 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft/libft.h"
# include "mlx42/include/MLX42/MLX42.h"

// PNG assets
# define WALL "./assets/wall.png"
# define PLAYER "./assets/player.png"
# define SPACE "./assets/space.png"
# define EXIT "./assets/exit.png"
# define COLLECTABLE "./assets/collectable.png"


typedef struct game_assets_s
{
	mlx_image_t	*wall;
	mlx_image_t	*player;
	mlx_image_t	*collectible;
	mlx_image_t	*exit;
	mlx_image_t	*space;

}	t_game_assets;

typedef struct game_textures_s
{
	mlx_texture_t	*wall;
	mlx_texture_t	*player;
	mlx_texture_t	*collectible;
	mlx_texture_t	*exit;
	mlx_texture_t	*space;
}	t_game_textures;

typedef struct map_size_s
{
	int32_t	width;
	int32_t	height;
}	t_map_size;

typedef struct elem_size_s
{
	double	width;
	double	height;
}	t_elem_size;

typedef struct display_size_s
{
	int32_t	width;
	int32_t	height;
}	t_display_size;

void				ft_add_graph_elm(char **map, t_game_assets *game_assets, mlx_t *mlx, t_elem_size elem_size);
char				**ft_generate_map(int height, int width);
void				ft_print_map(char **map);
t_game_assets		*ft_load_images(mlx_t *mlx, t_game_textures *game_textures);
void				ft_resize_assets(t_game_assets *game_assets, size_t x, size_t y);
t_game_textures		*ft_load_textures(void);
void				ft_del_textures(t_game_textures *game_textures);
t_elem_size			ft_cal_elem_size(t_map_size *map_size);
t_map_size			*ft_get_map_size(char **map);
#endif
