/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:42:02 by cchromos          #+#    #+#             */
/*   Updated: 2021/03/06 19:42:04 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grafic.h"

int				what_color(t_data *image, int tex_x, int tex_y)
{
	if ((image->ray_dir_x > 0) && (image->side == 0))
		return (my_mlx_pixel_get(image, tex_x, tex_y, 3));
	else if ((image->ray_dir_y > 0) && (image->side == 1))
		return (my_mlx_pixel_get(image, tex_x, tex_y, 2));
	else if ((image->ray_dir_y < 0) && (image->side == 1))
		return (my_mlx_pixel_get(image, tex_x, tex_y, 1));
	else if ((image->ray_dir_x < 0) && (image->side == 0))
		return (my_mlx_pixel_get(image, tex_x, tex_y, 4));
	return (0);
}

void			get_textures(t_data *image, int x, int tex_x)
{
	int			color;
	float		step;
	float		tex_pos;
	int			tex_y;

	step = 1.0 * image->north_height / image->line_height;
	tex_pos = (image->draw_start - image->resolution_y / 2 +
				image->line_height / 2) * step;
	while (image->draw_start <= image->draw_end)
	{
		tex_y = (int)tex_pos & (image->north_height - 1);
		tex_pos += step;
		color = what_color(image, tex_x, tex_y);
		my_mlx_pixel_put(image, x, image->draw_start, color);
		image->draw_start++;
	}
	return ;
}

void			draw3d(int x, t_data *image)
{
	float	wall_x;
	int		tex_x;

	image->draw_start = -1 * image->line_height / 2 + image->resolution_y / 2;
	if (image->draw_start < 0)
		image->draw_start = 0;
	image->draw_end = image->line_height / 2 + image->resolution_y / 2;
	if (image->draw_end >= image->resolution_y)
		image->draw_end = image->resolution_y - 1;
	if (image->side == 0)
		wall_x = image->pos_y + image->sprite->wall_dist[x] * image->ray_dir_y;
	else
		wall_x = image->pos_x + image->sprite->wall_dist[x] * image->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (float)image->north_width);
	if ((image->side == 0) && (image->ray_dir_x < 0))
		tex_x = image->north_width - tex_x - 1;
	if ((image->side == 1) && (image->ray_dir_y > 0))
		tex_x = image->north_width - tex_x - 1;
	get_textures(image, x, tex_x);
	return ;
}

int				other_flags(int flag, char **tex, int *bits_per_pixel,
																t_data *image)
{
	if (flag == 1)
	{
		*tex = image->north;
		*bits_per_pixel = image->north_bits_per_pixel;
		return (image->north_line_length);
	}
	else if (flag == 4)
	{
		*tex = image->west;
		*bits_per_pixel = image->west_bits_per_pixel;
		return (image->west_line_length);
	}
	else if (flag == 5)
	{
		*tex = image->sprite->path;
		*bits_per_pixel = image->sprite->bits_per_pixel;
		return (image->sprite->line_length);
	}
	return (0);
}

unsigned int	my_mlx_pixel_get(t_data *image, int x, int y, int flag)
{
	char	*dst;
	char	*tex;
	int		line_length;
	int		bits_per_pixel;

	line_length = 0;
	bits_per_pixel = 0;
	tex = NULL;
	if (flag == 3)
	{
		tex = image->east;
		line_length = image->east_line_length;
		bits_per_pixel = image->east_bits_per_pixel;
	}
	else if (flag == 2)
	{
		tex = image->south;
		line_length = image->south_line_length;
		bits_per_pixel = image->south_bits_per_pixel;
	}
	else if ((flag == 1) || (flag == 4) || (flag == 5))
		line_length = other_flags(flag, &tex, &bits_per_pixel, image);
	dst = tex + (y * line_length + x * (bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}
