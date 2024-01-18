/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 09:19:20 by orezek            #+#    #+#             */
/*   Updated: 2024/01/18 15:28:31 by orezek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_game_textures	*ft_load_textures(void)
{
	t_game_textures	*game_textures;

	game_textures = malloc(sizeof(t_game_textures));
	game_textures->player = mlx_load_png(PLAYER);
	game_textures->collectible = mlx_load_png(COLLECTABLE);
	game_textures->exit = mlx_load_png(EXIT);
	game_textures->space = mlx_load_png(SPACE);
	game_textures->wall = mlx_load_png(WALL);
	return (game_textures);
}

t_game_images	*ft_load_images(mlx_t *mlx, t_game_textures *game_textures)
{
	t_game_images	*game_assets;

	game_assets = malloc(sizeof(t_game_images));
	game_assets->player = mlx_texture_to_image(mlx, game_textures->player);
	game_assets->wall = mlx_texture_to_image
		(mlx, game_textures->wall);
	game_assets->collectible = mlx_texture_to_image
		(mlx, game_textures->collectible);
	game_assets->exit = mlx_texture_to_image(mlx, game_textures->exit);
	game_assets->space = mlx_texture_to_image(mlx, game_textures->space);
	return (game_assets);
}

void	ft_resize_assets(t_game_images *game_images, t_elem_size *elem_size)
{
	mlx_resize_image(game_images->player, elem_size->width, elem_size->height);
	mlx_resize_image
		(game_images->collectible, elem_size->width, elem_size->height);
	mlx_resize_image(game_images->wall, elem_size->width, elem_size->height);
	mlx_resize_image(game_images->exit, elem_size->width, elem_size->height);
}

void	ft_del_textures(t_game_textures *game_textures)
{
	mlx_delete_texture(game_textures->player);
	mlx_delete_texture(game_textures->wall);
	mlx_delete_texture(game_textures->collectible);
	mlx_delete_texture(game_textures->exit);
	mlx_delete_texture(game_textures->space);
}

t_game_images	*ft_load_graphics(mlx_t *mlx)
{
	t_game_textures	*game_textures;
	t_game_images	*game_images;

	game_textures = ft_load_textures();
	game_images = ft_load_images(mlx, game_textures);
	ft_del_textures(game_textures);
	free(game_textures);
	return (game_images);
}

// t_elem_size	*ft_get_element_size(t_map_size *map_size)
// {
// 	t_elem_size 	*elem_size;

// 	elem_size = malloc(sizeof(t_elem_size));
// 	if (!elem_size)
// 		return (NULL);
// 	elem_size->width = 1440 / map_size->width;
// 	elem_size->height = 960 / map_size->height;
// 	return (elem_size);
// }

void	ft_set_elem_size(t_game_context *game_context)
{
	t_elem_size 	*elem_size;
	t_map_size		*map_size;
	t_display_size	*display_size;

	if (!game_context->game_dimensions->map_size ||
	!game_context->game_dimensions->display_size)
		exit(1);
	elem_size = malloc(sizeof(t_elem_size));
	if (!elem_size)
		exit (1);
	map_size = game_context->game_dimensions->map_size;
	display_size = game_context->game_dimensions->display_size;
	elem_size->width = (display_size->width - 120) / map_size->width;
	elem_size->height = (display_size->height - 96) / map_size->height;
	game_context->game_dimensions->element_size = elem_size;
}
