/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:19:10 by cchromos          #+#    #+#             */
/*   Updated: 2021/01/23 13:19:12 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		check_struct(t_map_list *map)
{
	if ((map->resolution_x < 1) || (map->resolution_y < 1))
		return (3);
	if ((map->ceiling_r < 0) || (map->ceiling_g < 0) ||
			(map->ceiling_b < 0) || (map->floor_r < 0) ||
			(map->floor_g < 0) || (map->floor_b < 0) ||
			(map->ceiling_r > 255) || (map->ceiling_g > 255) ||
			(map->ceiling_b > 255) || (map->floor_r > 255) ||
			(map->floor_g > 255) || (map->floor_b > 255))
		return (3);
	if (!map->north || !map->south || !map->west || !map->east || !map->sprite)
		return (3);
	if ((ft_strlen(map->north) < 5) || (ft_strlen(map->south) < 5) ||
		(ft_strlen(map->east) < 5) || (ft_strlen(map->west) < 5) ||
		(ft_strlen(map->sprite) < 5))
		return (3);
	return (0);
}

int		work_with_struct(t_map_list *map, char **line)
{
	int				i;
	t_player_list	player;

	i = 0;
	player.count_of_players = 0;
	player.x_player = 0;
	player.y_player = 0;
	player.vector_of_player = '\0';
	player.to_free = line;
	if ((i = copy_map(line, map, &player)) == 0)
		init(map, &player);
	else
		return (3);
	return (i);
}

int		reading_file(char **line, int flag_save)
{
	int			i;
	t_map_list	map;

	i = 0;
	map.resolution_x = -1;
	map.resolution_y = -1;
	map.ceiling_r = -1;
	map.ceiling_g = -1;
	map.ceiling_b = -1;
	map.floor_r = -1;
	map.floor_g = -1;
	map.floor_b = -1;
	map.north = NULL;
	map.south = NULL;
	map.east = NULL;
	map.west = NULL;
	map.sprite = NULL;
	map.count_of_str_in_array = 0;
	map.len_of_str_in_array = 0;
	map.first_line_of_map = 0;
	map.last_line_of_map = 0;
	map.map_array = NULL;
	map.flag_save = flag_save;
	i = work_with_struct(&map, line);
	return (i);
}

int		filling_lines(int n, int fd, int flag_save)
{
	char	*lines[n + 1];
	int		i;
	int		gnl;

	i = 0;
	while ((gnl = get_next_line(fd, &lines[i])) > 0)
		i++;
	if (gnl == -1)
	{
		close(fd);
		return (4);
	}
	lines[n] = NULL;
	if (lines[n - 1][0] == '\0')
		return (3);
	close(fd);
	n = reading_file(lines, flag_save);
	while (i--)
		free(lines[i]);
	return (n);
}

int		continue_resolution(char *ptr)
{
	while (*ptr == ' ')
		ptr++;
	if (*ptr == '\0')
		return (0);
	return (3);
}
