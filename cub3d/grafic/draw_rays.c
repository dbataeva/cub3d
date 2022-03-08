/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:55:31 by cchromos          #+#    #+#             */
/*   Updated: 2021/02/04 16:55:33 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grafic.h"

int		x_step(t_data *image, int *map_x)
{
	if (image->ray_dir_y == 0)
		image->delta_dist_x = 0;
	else
	{
		if (image->ray_dir_x == 0)
			image->delta_dist_x = 1;
		else
			image->delta_dist_x = fabs(1 / image->ray_dir_x);
	}
	if (image->ray_dir_x < 0)
	{
		image->side_dist_x = (image->pos_x - *map_x) * image->delta_dist_x;
		return (-1);
	}
	else
	{
		image->side_dist_x = (*map_x + 1.0 - image->pos_x) *
															image->delta_dist_x;
		return (1);
	}
}

int		y_step(t_data *image, int *map_y)
{
	if (image->ray_dir_x == 0)
		image->delta_dist_y = 0;
	else
	{
		if (image->ray_dir_y == 0)
			image->delta_dist_y = 1;
		else
			image->delta_dist_y = fabs(1 / image->ray_dir_y);
	}
	if (image->ray_dir_y < 0)
	{
		image->side_dist_y = (image->pos_y - *map_y) * image->delta_dist_y;
		return (-1);
	}
	else
	{
		image->side_dist_y = (*map_y + 1.0 - image->pos_y) *
															image->delta_dist_y;
		return (1);
	}
}

int		steps_to_wall(int *map_x, int *map_y, t_data *image)
{
	image->step_x = x_step(image, map_x);
	image->step_y = y_step(image, map_y);
	if (image->side_dist_x < image->side_dist_y)
	{
		image->side_dist_x += image->delta_dist_x;
		*map_x += image->step_x;
		return (0);
	}
	else
	{
		image->side_dist_y += image->delta_dist_y;
		*map_y += image->step_y;
		return (1);
	}
}

void	draw_ray(t_data *image, int map_x, int map_y, int x)
{
	while (1)
	{
		image->side = steps_to_wall(&map_x, &map_y, image);
		if (check_wall(image->map, map_x, map_y) == 1)
			break ;
	}
	if (image->side == 0)
		image->sprite->wall_dist[x] = (map_x - image->pos_x +
									(1 - image->step_x) / 2) / image->ray_dir_x;
	else
		image->sprite->wall_dist[x] = (map_y - image->pos_y +
									(1 - image->step_y) / 2) / image->ray_dir_y;
	if (image->sprite->wall_dist[x] == 0)
		image->sprite->wall_dist[x] = 0.1;
	image->line_height = (int)(image->resolution_y /
								image->sprite->wall_dist[x]);
	image->line_height = (int)(image->line_height / image->koef);
	draw3d(x, image);
	return ;
}

void	my_mlx_pixel_put(t_data *image, int x, int y, int color)
{
	char *dst;

	dst = image->addr + (y * image->line_length + x *
			(image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
