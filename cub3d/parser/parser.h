/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:19:45 by cchromos          #+#    #+#             */
/*   Updated: 2021/01/23 13:19:47 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <stdlib.h>
# include "../../libft/libft.h"
# include "../../gnl/get_next_line.h"

typedef struct	s_map_list
{
	int		resolution_x;
	int		resolution_y;
	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*sprite;
	int		num_sprites;
	int		*sprite_on_map_x;
	int		*sprite_on_map_y;
	int		count_of_str_in_array;
	int		len_of_str_in_array;
	int		first_line_of_map;
	int		last_line_of_map;
	char	**map_array;
	int		flag_save;
}				t_map_list;
typedef struct	s_player_list
{
	int		count_of_players;
	int		x_player;
	int		y_player;
	char	vector_of_player;
	char	**to_free;
}				t_player_list;
int				filling_lines(int n, int fd, int flag_save);
int				copy_map(char **line, t_map_list *map, t_player_list *player);
int				filling_struct(char *line, t_map_list *map);
int				filling_struct_west_texture(char *ptr, t_map_list *map,
											char *line);
int				filling_struct_east_texture(char *ptr, t_map_list *map,
											char *line);
int				filling_struct_south_texture(char *ptr, t_map_list *map,
											char *line);
int				filling_struct_sprite(char *ptr, t_map_list *map, char *line);
void			is_player_here(char *line, char chr, t_player_list *player,
								int i);
int				flood_fill(t_player_list *player, t_map_list *map,
							char **array);
int				new_line(char **line, int max_len);
t_map_list		*new_struct(void);
int				check_array(char **array, int last_line, t_map_list *map);
void			init(t_map_list *map, t_player_list *player);
int				check_struct(t_map_list *map);
void			count_len_of_str_in_array(t_map_list *map, char **line);
int				writing_path_sprite(char *check, char *ptr, t_map_list *map);
int				writing_path_south(char *check, char *ptr, t_map_list *map);
int				writing_path_east(char *check, char *ptr, t_map_list *map);
int				writing_path_west(char *check, char *ptr, t_map_list *map);
int				writing_path_north(char *check, char *ptr, t_map_list *map);
int				continue_ceiling(char *ptr, t_map_list *map);
int				continue_floor(char *ptr, t_map_list *map);
int				check_other_symbols(t_map_list *map, char **line);
int				continue_resolution(char *ptr);

#endif
