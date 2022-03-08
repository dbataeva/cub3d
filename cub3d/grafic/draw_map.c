/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:52:58 by cchromos          #+#    #+#             */
/*   Updated: 2021/02/04 16:53:00 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grafic.h"

void	draw_player(t_data *image)
{
	int		x;
	float	camera_x;

	x = 0;
	while (x < image->resolution_x)
	{
		camera_x = 2 * x / (float)image->resolution_x - 1;
		image->ray_dir_x = image->dir_x + image->plane_x * camera_x;
		image->ray_dir_y = image->dir_y + image->plane_y * camera_x;
		draw_ray(image, image->pos_x, image->pos_y, x);
		x++;
	}
	return ;
}

void	draw_floor_ceiling(t_data *image)
{
	int i;
	int j;

	i = 0;
	while (i < (image->resolution_y / 2))
	{
		j = 0;
		while (j < image->resolution_x)
		{
			my_mlx_pixel_put(image, j, i, image->ceiling);
			j++;
		}
		i++;
	}
	while (i < (image->resolution_y))
	{
		j = 0;
		while (j < image->resolution_x)
		{
			my_mlx_pixel_put(image, j, i, image->floor);
			j++;
		}
		i++;
	}
	return ;
}

int		draw(t_data *image)
{
	draw_floor_ceiling(image);
	if (image->keys->w)
		key_w(image);
	if (image->keys->a)
		key_a(image);
	if (image->keys->s)
		key_s(image);
	if (image->keys->d)
		key_d(image);
	if ((image->keys->r) || (image->keys->l))
		keys_rigth_left(image);
	draw_player(image);
	if (image->sprite->num_sprites != 0)
		draw_sprites(image);
	if (image->flag_save == 1)
		screen_save(image);
	mlx_put_image_to_window(image->mlx, image->mlx_win, image->img, 0, 0);
	return (0);
}

void	ft_free(t_data *image)
{
	int i;

	i = 0;
	while (image->to_free[i])
	{
		free(image->to_free[i]);
		i++;
	}
	if (image->sprite->wall_dist)
		free(image->sprite->wall_dist);
	if (image->sprite->sprite_on_map_y)
		free(image->sprite->sprite_on_map_y);
	if (image->sprite->sprite_on_map_x)
		free(image->sprite->sprite_on_map_x);
	if (image->sprite->dist_to_sprite)
		free(image->sprite->dist_to_sprite);
	if (image->img)
		free(image->img);
	if (image->mlx)
		free(image->mlx);
	if (image->mlx_win)
		free(image->mlx_win);
	return ;
}

int		if_exit(t_data *image, int out)
{
	ft_free(image);
	if (out == 0)
		exit(0);
	else
	{
		if (out == 1)
			write(2, "Error\nError of memory\n", 22);
		if (out == 2)
			write(2, "Error\nError of texture\n", 23);
		if (out == 3)
			write(2, "Error\nError of opening\n", 23);
		exit(1);
	}
	return (0);
}
