/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:51:18 by cchromos          #+#    #+#             */
/*   Updated: 2021/01/27 11:51:20 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grafic.h"

int		new_image(t_data *image, t_map_list *map, t_sprite *sprite)
{
	image->flag_save = map->flag_save;
	sprite->path = map->sprite;
	image->sprite = sprite;
	xpm_file_to_image(image);
	if (!(image->img = mlx_new_image(image->mlx, image->resolution_x,
						image->resolution_y)))
		if_exit(image, 1);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
					&image->line_length, &image->endian);
	image->floor = create_rgb(map->floor_r, map->floor_g, map->floor_b);
	image->ceiling = create_rgb(map->ceiling_r, map->ceiling_g, map->ceiling_b);
	sprite->num_sprites = map->num_sprites;
	sprite->sprite_on_map_x = map->sprite_on_map_x;
	sprite->sprite_on_map_y = map->sprite_on_map_y;
	change_xy(sprite);
	image->koef = 1;
	if (image->resolution_x / image->resolution_y != 1.333333)
		image->koef = 1.333333 * image->resolution_y / image->resolution_x;
	draw(image);
	mlx_hook(image->mlx_win, 2, 1L << 0, key_press, image);
	mlx_hook(image->mlx_win, 3, 1L << 1, key_release, image);
	mlx_hook(image->mlx_win, 17, 1L << 0, if_exit, image);
	mlx_loop_hook(image->mlx, draw, image);
	mlx_loop(image->mlx);
	return (0);
}

void	fill_player_info(t_player_list *player, t_data *image)
{
	if (player->vector_of_player == 'N')
	{
		image->dir_y = -1;
		image->dir_x = 0;
		image->plane_x = 0.66;
		image->plane_y = 0;
	}
	else if (player->vector_of_player == 'S')
	{
		image->dir_y = 1;
		image->dir_x = 0;
		image->plane_x = -0.66;
		image->plane_y = 0;
	}
	else if (player->vector_of_player == 'E')
	{
		image->dir_x = 1;
		image->dir_y = 0;
		image->plane_x = 0;
		image->plane_y = 0.66;
	}
	utils(image, player);
}

void	get_screen_size(t_map_list *map, t_data *image, int *width, int *height)
{
	mlx_get_screen_size(width, height);
	if (((map->resolution_x > *width) || (map->resolution_y > *height)) &&
																!map->flag_save)
	{
		image->resolution_x = *width;
		image->resolution_y = *height;
	}
	else if ((map->flag_save) && ((map->resolution_x > 16384) ||
												(map->resolution_y > 16384)))
	{
		if (map->resolution_x > 16384)
			image->resolution_x = 16384;
		if (map->resolution_y > 16384)
			image->resolution_y = 16384;
	}
	else
	{
		image->resolution_x = map->resolution_x;
		image->resolution_y = map->resolution_y;
	}
	image->north = map->north;
	image->south = map->south;
	image->east = map->east;
	image->west = map->west;
	image->map = map->map_array;
}

void	init(t_map_list *map, t_player_list *player)
{
	t_data		image;
	t_sprite	sprite;
	t_keys		keys;
	int			width;
	int			height;

	image.img = NULL;
	image.mlx = NULL;
	image.mlx_win = NULL;
	image.mlx = mlx_init();
	get_screen_size(map, &image, &width, &height);
	sprite.wall_dist = NULL;
	sprite.num_sprites = map->num_sprites;
	sprite.sprite_on_map_y = map->sprite_on_map_y;
	sprite.sprite_on_map_x = map->sprite_on_map_x;
	sprite.dist_to_sprite = NULL;
	if (!(sprite.wall_dist = (float *)malloc(sizeof(float) *
													image.resolution_x + 1)))
		if_exit(&image, 1);
	if ((map->flag_save == 0) && !(image.mlx_win = mlx_new_window(image.mlx,
							image.resolution_x, image.resolution_y, "Cub3D")))
		if_exit(&image, 1);
	image.keys = &keys;
	fill_player_info(player, &image);
	new_image(&image, map, &sprite);
}
