/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grafic.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:49:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/02/04 16:49:42 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAFIC_H
# define GRAFIC_H

# include "../minilibx/mlx.h"
# include "../parser/parser.h"
# include <math.h>

typedef struct		s_sprite
{
	char			*path;
	int				xpm_width;
	int				xpm_height;
	int				bits_per_pixel;
	int				line_length;
	float			*wall_dist;
	int				num_sprites;
	int				*sprite_on_map_x;
	int				*sprite_on_map_y;
	float			*dist_to_sprite;
	float			sprite_x;
	float			sprite_y;
	float			transform_x;
	float			transform_y;
	int				sprite_screen_x;
	int				height;
	int				draw_start_y;
	int				draw_end_y;
	int				width;
	int				draw_start_x;
	int				draw_end_x;
	int				tex_x;
	int				tex_y;
	float			inv_det;
	int				color;
}					t_sprite;
typedef struct		s_keys
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				r;
	int				l;
}					t_keys;
typedef struct		s_data
{
	void			*mlx;
	void			*mlx_win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	char			**map;
	int				flag_save;
	int				resolution_x;
	int				resolution_y;
	float			koef;
	float			pos_x;
	float			pos_y;
	char			player;
	float			dir_x;
	float			old_dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	float			old_plane_x;
	float			ray_dir_x;
	float			ray_dir_y;
	float			delta_dist_y;
	float			delta_dist_x;
	int				step_x;
	int				step_y;
	float			side_dist_x;
	float			side_dist_y;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	float			new_angle;
	float			old_angle;
	float			delta_angle;
	char			**to_free;
	int				floor;
	int				ceiling;
	char			*north;
	int				north_width;
	int				north_height;
	int				north_bits_per_pixel;
	int				north_line_length;
	char			*south;
	int				south_width;
	int				south_height;
	int				south_bits_per_pixel;
	int				south_line_length;
	char			*east;
	int				east_width;
	int				east_height;
	int				east_bits_per_pixel;
	int				east_line_length;
	char			*west;
	int				west_width;
	int				west_height;
	int				west_bits_per_pixel;
	int				west_line_length;
	t_keys			*keys;
	t_sprite		*sprite;
}					t_data;
typedef	struct		s_screen
{
	int				file_type[2];
	unsigned int	file_size;
	unsigned int	reserved;
	unsigned int	pixel_data_offset;
	unsigned int	header_size;
	int				image_width;
	int				image_height;
	unsigned int	planes;
	unsigned int	bits_per_pixel;
	unsigned int	compression;
	unsigned int	image_size;
	int				x_pixels_per_meter;
	int				y_pixels_per_meter;
	unsigned int	total_colors;
	unsigned int	important_colors;
}					t_screen;
int					draw(t_data *image);
int					key_press(int keycode, t_data *image);
int					key_release(int keycode, t_data *image);
void				keys_rigth_left(t_data *image);
void				key_a(t_data *image);
void				key_d(t_data *image);
void				key_s(t_data *image);
void				key_w(t_data *image);
void				my_mlx_pixel_put(t_data *image, int x, int y, int color);
void				draw_ray(t_data *image, int map_x, int map_y, int x);
int					check_wall(char **map, int x, int y);
int					new_draw(t_data *image);
void				draw3d(int x, t_data *image);
int					if_exit(t_data *image, int out);
void				draw_sprites(t_data *image);
int					what_is_sprite_dist(t_data *image, int map_x, int map_y);
unsigned int		my_mlx_pixel_get(t_data *image, int x, int y, int flag);
void				screen_save(t_data *image);
void				ft_putnbr_base(int nbr, char *base, int fd);
void				swap(t_sprite *sprite, int j);
int					create_rgb(int r, int g, int b);
void				xpm_file_to_image(t_data *image);
void				change_xy(t_sprite *sprite);
void				utils(t_data *image, t_player_list *player);

#endif
