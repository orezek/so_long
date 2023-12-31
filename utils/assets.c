/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezek <orezek@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:40:49 by orezek            #+#    #+#             */
/*   Updated: 2023/12/28 19:46:08 by orezek           ###   ########.fr       */
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


t_game_assets	*ft_load_images(mlx_t *mlx, t_game_textures *game_textures)
{
	t_game_assets	*game_assets;
	game_assets = malloc(sizeof(t_game_assets));
	game_assets->player = mlx_texture_to_image(mlx, game_textures->player);
	game_assets->wall = mlx_texture_to_image(mlx, game_textures->wall);
	game_assets->collectible = mlx_texture_to_image(mlx, game_textures->collectible);
	game_assets->exit = mlx_texture_to_image(mlx, game_textures->exit);
	game_assets->space = mlx_texture_to_image(mlx, game_textures->space);
	return (game_assets);
}

void ft_resize_assets(t_game_assets *game_assets, size_t x, size_t y)
{
	mlx_resize_image(game_assets->player, y, x);
	mlx_resize_image(game_assets->collectible, y, x);
	mlx_resize_image(game_assets->wall, y, x);
	mlx_resize_image(game_assets->exit, y, x);
}

void ft_del_textures(t_game_textures *game_textures)
{
	// cleanup
	mlx_delete_texture(game_textures->player);
	mlx_delete_texture(game_textures->wall);
	mlx_delete_texture(game_textures->collectible);
	mlx_delete_texture(game_textures->exit);
	mlx_delete_texture(game_textures->space);
	free(game_textures);
}
