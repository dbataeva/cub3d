/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:04:47 by cchromos          #+#    #+#             */
/*   Updated: 2021/03/07 13:04:49 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grafic.h"

void	key_w(t_data *image)
{
	if (image->keys->w)
	{
		if ((check_wall(image->map, (image->pos_x + image->dir_x / 2),
		(image->pos_y + image->dir_y / 2)) == 0) && (check_wall(image->map,
		(image->pos_x + image->dir_x / 2 + image->plane_x / 3), (image->pos_y +
		image->dir_y / 2 + image->plane_y / 3)) == 0) && (check_wall(image->map,
		(image->pos_x + image->dir_x / 2 - image->plane_x / 3), (image->pos_y +
		image->dir_y / 2 - image->plane_y / 3)) == 0))
		{
			image->pos_x += image->dir_x / 10;
			image->pos_y += image->dir_y / 10;
		}
	}
	return ;
}

void	key_s(t_data *image)
{
	if (image->keys->s)
	{
		if ((check_wall(image->map, (image->pos_x - image->dir_x / 2),
		(image->pos_y - image->dir_y / 2)) == 0) && (check_wall(image->map,
		(image->pos_x - image->dir_x / 2 - image->plane_x / 3), (image->pos_y -
		image->dir_y / 2 - image->plane_y / 3)) == 0) && (check_wall(image->map,
		(image->pos_x - image->dir_x / 2 + image->plane_x / 3), (image->pos_y -
		image->dir_y / 2) + image->plane_y / 3) == 0))
		{
			image->pos_x -= image->dir_x / 10;
			image->pos_y -= image->dir_y / 10;
		}
	}
	return ;
}

void	key_a(t_data *image)
{
	if (image->keys->a)
	{
		if (((check_wall(image->map, (image->pos_x - image->plane_x / 2),
		(image->pos_y - image->plane_y / 2))) == 0) && ((check_wall(image->map,
		(image->pos_x - image->plane_x / 2 - image->dir_x / 3), (image->pos_y -
		image->plane_y / 2 - image->dir_y / 3))) == 0) &&
		((check_wall(image->map, (image->pos_x - image->plane_x / 2 +
		image->dir_x / 3), (image->pos_y - image->plane_y / 2 + image->dir_y /
		3))) == 0))
		{
			image->pos_x -= image->plane_x / 10;
			image->pos_y -= image->plane_y / 10;
		}
	}
	return ;
}

void	key_d(t_data *image)
{
	if (image->keys->d)
	{
		if (((check_wall(image->map, (image->pos_x + image->plane_x / 2),
		(image->pos_y + image->plane_y / 2))) == 0) && ((check_wall(image->map,
		(image->pos_x + image->plane_x / 2 + image->dir_x / 3), (image->pos_y +
		image->plane_y / 2 + image->dir_y / 3))) == 0) &&
		((check_wall(image->map, (image->pos_x + image->plane_x / 2 -
		image->dir_x / 3), (image->pos_y + image->plane_y / 2 - image->dir_y /
		3))) == 0))
		{
			image->pos_x += image->plane_x / 10;
			image->pos_y += image->plane_y / 10;
		}
	}
	return ;
}

void	keys_rigth_left(t_data *image)
{
	if (image->keys->l)
		image->delta_angle = -0.05;
	else if (image->keys->r)
		image->delta_angle = 0.05;
	image->old_dir_x = image->dir_x;
	image->dir_x = image->dir_x * cos(image->delta_angle) -
					image->dir_y * sin(image->delta_angle);
	image->dir_y = image->old_dir_x * sin(image->delta_angle) +
					image->dir_y * cos(image->delta_angle);
	image->old_plane_x = image->plane_x;
	image->plane_x = image->plane_x * cos(image->delta_angle) -
						image->plane_y * sin(image->delta_angle);
	image->plane_y = image->old_plane_x * sin(image->delta_angle) +
						image->plane_y * cos(image->delta_angle);
	return ;
}
