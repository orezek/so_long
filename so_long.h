/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:27:03 by aldokezer         #+#    #+#             */
/*   Updated: 2024/01/18 09:25:01 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft/libft.h"
# include "mlx42/include/MLX42/MLX42.h"
# include <fcntl.h>

// PNG assets
# define WALL "./assets/wall.png"
# define PLAYER "./assets/player.png"
# define SPACE "./assets/space.png"
# define EXIT "./assets/exit.png"
# define COLLECTABLE "./assets/collectable.png"

// default window size
# define WIDTH 1680
# define HEIGHT 1050

// Aliases
typedef int32_t	t_player_moves;

// Structs
typedef struct game_images_s
{
	mlx_image_t	*wall;
	mlx_image_t	*player;
	mlx_image_t	*collectible;
	mlx_image_t	*exit;
	mlx_image_t	*space;

}	t_game_images;

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
	int32_t	width;
	int32_t	height;
}	t_elem_size;

typedef struct display_size_s
{
	int32_t	width;
	int32_t	height;
}	t_display_size;

typedef struct game_dimensions_s
{
	t_display_size	*display_size;
	t_map_size		*map_size;
	t_elem_size		*element_size;
}	t_game_dimensions;

typedef struct player_position_s
{
	int32_t	x;
	int32_t	y;
}	t_player_position;

typedef struct player_s
{
	t_player_moves		player_moves;
	t_player_position	*player_position;
}	t_player;

typedef struct exit_position_s
{
	int32_t	x;
	int32_t	y;
}	t_exit_position;

typedef struct collectable_s
{
	int	no_collectables;
	int	remaining_collectables;
}	t_collectable;

typedef struct map_s
{
	char	**original_map;
	char	**flooded_map;
}	t_map;

typedef struct game_context_s
{
	t_collectable		*collectables;
	t_map				*map;
	t_game_dimensions	*game_dimensions;
	t_game_images		*game_images;
	t_player			*player;
	t_exit_position		*exit_position;
}	t_game_context;

void				ft_render_game_map(mlx_t *mlx, t_game_context *game_context);
void				ft_print_map(char **map);
t_game_images		*ft_load_images(mlx_t *mlx, t_game_textures *game_textures);
void				ft_resize_assets(t_game_images *game_images,
						t_elem_size *elem_size);
t_game_textures		*ft_load_textures(void);
void				ft_del_textures(t_game_textures *game_textures);
void				ft_get_element_size(t_game_context *game_context);
t_map_size			*ft_get_map_size(char **map);
char				**ft_load_map(char *map_path);
t_game_images		*ft_load_graphics(mlx_t *mlx);
mlx_t				*ft_game_init(t_game_context *game_context);
int					ft_free_array(char **array);
void				on_key_press(mlx_key_data_t k_data, void *param);
void				on_window_resize(int32_t width, int32_t height,
						void *param);
void				ft_release_game_resources(mlx_t *mlx, t_game_context *game_context);
t_player_position	*ft_get_player_position(char **map);
size_t				ft_count_collectibles(t_game_context *game_context);
int					ft_check_collectibles(t_game_context *game_context);
t_exit_position		*ft_get_exit_position(char **map);
int					ft_end_game(t_game_context *game_context);
void				ft_get_display_size(t_game_context *game_context);
void				*ft_duplicate_map(t_game_context *game_context);
void				ft_map_flood(char	**map_to_flood, size_t y, size_t x);
int32_t				ft_map_char_count(char **map, char char_to_search);
void				ft_verify_game_map(char **loaded_map, char **flooded_map);
int32_t				ft_check_file_name(char *str);
int32_t				ft_validate_map_dimensions(char **map);
int32_t				ft_check_map_boundary(char **map);
void				ft_check_program_arguments(int32_t argct, const char *argvt[]);
#endif
