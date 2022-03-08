/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:24:04 by cchromos          #+#    #+#             */
/*   Updated: 2021/03/07 13:24:05 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grafic.h"

void	change_width_and_height(t_data *image, void *img, int endian)
{
	if (!(img = mlx_xpm_file_to_image(image->mlx, image->sprite->path,
						&image->sprite->xpm_width, &image->sprite->xpm_height)))
		if_exit(image, 2);
	image->sprite->path = mlx_get_data_addr(img, &image->sprite->bits_per_pixel,
										&image->sprite->line_length, &endian);
	if (image->north_width != 64)
		image->north_width = 64;
	if (image->north_height != 64)
		image->north_height = 64;
	if (image->south_height != 64)
		image->south_height = 64;
	if (image->south_width != 64)
		image->south_width = 64;
	if (image->west_height != 64)
		image->west_height = 64;
	if (image->west_width != 64)
		image->west_width = 64;
	if (image->east_height != 64)
		image->east_height = 64;
	if (image->east_width != 64)
		image->east_width = 64;
	if (image->sprite->xpm_height != 64)
		image->sprite->xpm_height = 64;
	if (image->sprite->xpm_width != 64)
		image->sprite->xpm_width = 64;
}

void	xpm_file_to_image(t_data *image)
{
	void	*img;
	int		endian;

	if (!(img = mlx_xpm_file_to_image(image->mlx, image->north,
				&image->north_width, &image->north_height)))
		if_exit(image, 2);
	image->north = mlx_get_data_addr(img, &image->north_bits_per_pixel,
									&image->north_line_length, &endian);
	if (!(img = mlx_xpm_file_to_image(image->mlx, image->south,
				&image->south_width, &image->south_height)))
		if_exit(image, 2);
	image->south = mlx_get_data_addr(img, &image->south_bits_per_pixel,
									&image->south_line_length, &endian);
	if (!(img = mlx_xpm_file_to_image(image->mlx, image->east,
				&image->east_width, &image->east_height)))
		if_exit(image, 2);
	image->east = mlx_get_data_addr(img, &image->east_bits_per_pixel,
									&image->east_line_length, &endian);
	if (!(img = mlx_xpm_file_to_image(image->mlx, image->west,
				&image->west_width, &image->west_height)))
		if_exit(image, 2);
	image->west = mlx_get_data_addr(img, &image->west_bits_per_pixel,
									&image->west_line_length, &endian);
	change_width_and_height(image, img, endian);
}

void	change_xy(t_sprite *sprite)
{
	int *swap;

	swap = sprite->sprite_on_map_x;
	sprite->sprite_on_map_x = sprite->sprite_on_map_y;
	sprite->sprite_on_map_y = swap;
	return ;
}

int		key_press(int keycode, t_data *image)
{
	if (keycode == 13)
		image->keys->w = 1;
	if (keycode == 1)
		image->keys->s = 1;
	if (keycode == 0)
		image->keys->a = 1;
	if (keycode == 2)
		image->keys->d = 1;
	if (keycode == 123)
		image->keys->l = 1;
	if (keycode == 124)
		image->keys->r = 1;
	if (keycode == 53)
		if_exit(image, 0);
	return (0);
}

int		key_release(int keycode, t_data *image)
{
	if (keycode == 13)
		image->keys->w = 0;
	if (keycode == 1)
		image->keys->s = 0;
	if (keycode == 0)
		image->keys->a = 0;
	if (keycode == 2)
		image->keys->d = 0;
	if (keycode == 123)
		image->keys->l = 0;
	if (keycode == 124)
		image->keys->r = 0;
	return (0);
}
