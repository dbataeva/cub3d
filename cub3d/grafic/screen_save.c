/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_save.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:23:45 by cchromos          #+#    #+#             */
/*   Updated: 2021/03/07 13:23:47 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grafic.h"

void	ft_write(t_screen *shot, t_data *image, int fd)
{
	write(fd, &shot->file_type[0], 1);
	write(fd, &shot->file_type[1], 1);
	write(fd, &shot->file_size, 4);
	write(fd, &shot->reserved, 2);
	write(fd, &shot->reserved, 2);
	write(fd, &shot->pixel_data_offset, 4);
	write(fd, &shot->header_size, 4);
	write(fd, &shot->image_width, 4);
	write(fd, &shot->image_height, 4);
	write(fd, &shot->planes, 2);
	write(fd, &shot->bits_per_pixel, 2);
	write(fd, &shot->compression, 4);
	write(fd, &shot->image_size, 4);
	write(fd, &shot->x_pixels_per_meter, 4);
	write(fd, &shot->y_pixels_per_meter, 4);
	write(fd, &shot->total_colors, 4);
	write(fd, &shot->important_colors, 4);
	write(fd, image->addr, image->resolution_x * image->resolution_y * 4);
	return ;
}

void	screen_save(t_data *image)
{
	int			fd;
	t_screen	shot;

	shot.file_type[0] = 0x42;
	shot.file_type[1] = 0x4D;
	shot.file_size = 54 + image->resolution_x * image->resolution_y * 4;
	shot.reserved = 0x00000000;
	shot.pixel_data_offset = 0x36;
	shot.header_size = 40;
	shot.image_width = image->resolution_x;
	shot.image_height = -image->resolution_y;
	shot.planes = 1;
	shot.bits_per_pixel = image->bits_per_pixel;
	shot.compression = 0;
	shot.image_size = image->resolution_x * image->resolution_y * 4;
	shot.x_pixels_per_meter = 0;
	shot.y_pixels_per_meter = 0;
	shot.total_colors = 0;
	shot.important_colors = 0;
	if ((fd = open("screen.bmp", O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU)) == -1)
		if_exit(image, 3);
	ft_write(&shot, image, fd);
	close(fd);
	if_exit(image, 0);
	return ;
}

int		check_wall(char **map, int x, int y)
{
	if (map[y][x] == '1')
		return (1);
	return (0);
}

void	swap(t_sprite *sprite, int j)
{
	int		swap_xy;
	float	swap_dist;

	swap_dist = sprite->dist_to_sprite[j];
	sprite->dist_to_sprite[j] = sprite->dist_to_sprite[j + 1];
	sprite->dist_to_sprite[j + 1] = swap_dist;
	swap_xy = sprite->sprite_on_map_x[j];
	sprite->sprite_on_map_x[j] = sprite->sprite_on_map_x[j + 1];
	sprite->sprite_on_map_x[j + 1] = swap_xy;
	swap_xy = sprite->sprite_on_map_y[j];
	sprite->sprite_on_map_y[j] = sprite->sprite_on_map_y[j + 1];
	sprite->sprite_on_map_y[j + 1] = swap_xy;
	return ;
}

int		create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
