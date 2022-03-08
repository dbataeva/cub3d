/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:34:50 by cchromos          #+#    #+#             */
/*   Updated: 2021/03/13 15:31:34 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grafic.h"

void	sort_sprites(t_sprite *sprite, t_data *image)
{
	int		i;
	int		j;

	i = -1;
	if (!(sprite->dist_to_sprite = (float *)malloc(sizeof(float) *
													sprite->num_sprites)))
		if_exit(image, 1);
	while (++i < sprite->num_sprites)
	{
		sprite->dist_to_sprite[i] = pow((image->pos_x -
		sprite->sprite_on_map_x[i]), 2) + pow((image->pos_y -
										image->sprite->sprite_on_map_y[i]), 2);
	}
	i = -1;
	while (++i < sprite->num_sprites - 1)
	{
		j = 0;
		while (j < sprite->num_sprites - 1)
		{
			if (sprite->dist_to_sprite[j] < sprite->dist_to_sprite[j + 1])
				swap(sprite, j);
			j++;
		}
	}
	return ;
}

void	draw_start_and_end(t_data *image, int i)
{
	image->sprite->sprite_x = image->sprite->sprite_on_map_x[i] -
								image->pos_x + 0.5;
	image->sprite->sprite_y = image->sprite->sprite_on_map_y[i] -
								image->pos_y + 0.5;
	image->sprite->inv_det = 1.0 / (image->plane_x * image->dir_y -
											image->dir_x * image->plane_y);
	image->sprite->transform_x = image->sprite->inv_det * (image->dir_y *
		image->sprite->sprite_x - image->dir_x * image->sprite->sprite_y);
	image->sprite->transform_y = image->sprite->inv_det * (-image->plane_y *
		image->sprite->sprite_x + image->plane_x * image->sprite->sprite_y);
	image->sprite->sprite_screen_x = (int)((image->resolution_x / 2) * (1 +
				image->sprite->transform_x / image->sprite->transform_y));
	image->sprite->height = abs((int)(image->resolution_y /
									image->sprite->transform_y / image->koef));
	image->sprite->draw_start_y = -image->sprite->height / 2 +
													image->resolution_y / 2;
	if (image->sprite->draw_start_y < 0)
		image->sprite->draw_start_y = 0;
	image->sprite->draw_end_y = image->sprite->height / 2 +
													image->resolution_y / 2;
	if (image->sprite->draw_end_y >= image->resolution_y)
		image->sprite->draw_end_y = image->resolution_y - 1;
	return ;
}

void	draw_start_x(t_data *image)
{
	image->sprite->width = abs((int)(image->resolution_x /
									image->sprite->transform_y));
	image->sprite->draw_start_x = -image->sprite->width / 2 +
											image->sprite->sprite_screen_x;
	if (image->sprite->draw_start_x < 0)
		image->sprite->draw_start_x = 0;
	image->sprite->draw_end_x = image->sprite->width / 2 +
											image->sprite->sprite_screen_x;
	if (image->sprite->draw_end_x >= image->resolution_x)
		image->sprite->draw_end_x = image->resolution_x - 1;
	return ;
}

void	draw_tex(t_data *image, int stripe, int y)
{
	int		d;

	image->sprite->tex_x = (int)(256 * (stripe - (-image->sprite->width
	/ 2 + image->sprite->sprite_screen_x)) * image->sprite->xpm_width /
											image->sprite->width / 256);
	if ((image->sprite->transform_y > 0) && (stripe < image->resolution_x) &&
		(image->sprite->transform_y < image->sprite->wall_dist[stripe]) &&
		(stripe > 0))
	{
		y = image->sprite->draw_start_y;
		while (y < image->sprite->draw_end_y)
		{
			d = y * 256 - image->resolution_y * 128 + image->sprite->height *
																			128;
			image->sprite->tex_y = ((d * image->sprite->xpm_height)
												/ image->sprite->height) / 256;
			image->sprite->color = my_mlx_pixel_get(image, image->sprite->tex_x,
			image->sprite->tex_y, 5);
			if ((image->sprite->color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(image, stripe, y, image->sprite->color);
			y++;
		}
	}
	return ;
}

void	draw_sprites(t_data *image)
{
	int		i;
	int		y;
	int		stripe;

	if (image->sprite->dist_to_sprite)
		free(image->sprite->dist_to_sprite);
	sort_sprites(image->sprite, image);
	i = 0;
	y = 0;
	while (i < image->sprite->num_sprites)
	{
		draw_start_and_end(image, i);
		draw_start_x(image);
		stripe = image->sprite->draw_start_x;
		while (stripe < image->sprite->draw_end_x)
		{
			draw_tex(image, stripe, y);
			stripe++;
		}
		i++;
	}
	return ;
}
