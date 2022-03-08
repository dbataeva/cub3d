/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:45:28 by cchromos          #+#    #+#             */
/*   Updated: 2021/01/22 20:45:30 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		filling_struct_resolution(char *ptr, char *line, t_map_list *map, int i)
{
	while (line[i] == ' ')
		i++;
	if ((line[i] != 'R') || (map->resolution_x != -1) ||
													(map->resolution_y != -1))
		return (3);
	ptr++;
	while (*ptr == ' ')
		ptr++;
	while (*ptr == '0')
		ptr++;
	if (*ptr == ' ')
		return (3);
	map->resolution_x = ft_atoi(ptr);
	while ((*ptr >= '0') && (*ptr <= '9'))
		ptr++;
	while (*ptr == ' ')
		ptr++;
	while (*ptr == '0')
		ptr++;
	if ((*ptr == ' ') || (*ptr == '\0'))
		return (3);
	map->resolution_y = ft_atoi(ptr);
	while ((*ptr >= '0') && (*ptr <= '9'))
		ptr++;
	return (continue_resolution(ptr));
}

int		filling_struct_ceiling(char *ptr, t_map_list *map, char *line, int i)
{
	while (line[i] == ' ')
		i++;
	if (line[i] != 'C')
		return (3);
	ptr++;
	while (*ptr == ' ')
		ptr++;
	while (*ptr == '0')
		ptr++;
	if ((*ptr == ',') && (*(ptr - 1) == '0'))
		map->ceiling_r = 0;
	else if ((!((*ptr >= '1') && (*ptr <= '9')) && (*ptr != '-') &&
								(*(ptr + 1) != 0)) || (map->ceiling_r != -1))
		return (3);
	else
		map->ceiling_r = ft_atoi(ptr);
	if (*ptr == '-')
		ptr++;
	while ((*ptr >= '0') && (*ptr <= '9'))
		ptr++;
	while (*ptr == ' ')
		ptr++;
	if (*(ptr++) != ',')
		return (3);
	return (continue_ceiling(ptr, map));
}

int		filling_struct_floor(char *ptr, t_map_list *map, char *line, int i)
{
	while (line[i] == ' ')
		i++;
	if (line[i] != 'F')
		return (3);
	ptr++;
	while (*ptr == ' ')
		ptr++;
	while (*ptr == '0')
		ptr++;
	if ((*ptr == ',') && (*(ptr - 1) == '0'))
		map->floor_r = 0;
	else if ((!((*ptr >= '1') && (*ptr <= '9')) && (*ptr != '-') &&
									(*(ptr + 1) != 0)) || (map->floor_r != -1))
		return (3);
	else
		map->floor_r = ft_atoi(ptr);
	if (*ptr == '-')
		ptr++;
	while ((*ptr >= '0') && (*ptr <= '9'))
		ptr++;
	while (*ptr == ' ')
		ptr++;
	if (*(ptr++) != ',')
		return (3);
	return (continue_floor(ptr, map));
}

int		filling_struct_north_texture(char *ptr, t_map_list *map, char *line)
{
	char	*check;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] != 'N')
		return (3);
	if (*(++ptr) != 'O')
		return (3);
	if (map->north)
		return (3);
	ptr++;
	while (*ptr == ' ')
		ptr++;
	if ((check = ft_strnstr(ptr, ".xpm", ft_strlen(ptr))))
		return (writing_path_north(check, ptr, map));
	return (3);
}

int		filling_struct(char *line, t_map_list *map)
{
	char	*ptr;

	if ((ptr = ft_strchr(line, 'R')) &&
						(filling_struct_resolution(ptr, line, map, 0) != 0))
		return (3);
	if ((ptr = ft_strchr(line, 'C')) &&
							(filling_struct_ceiling(ptr, map, line, 0) != 0))
		return (3);
	if ((ptr = ft_strchr(line, 'F')) &&
								(filling_struct_floor(ptr, map, line, 0) != 0))
		return (3);
	if ((ptr = ft_strchr(line, 'N')) &&
							(filling_struct_north_texture(ptr, map, line) != 0))
		return (3);
	if ((ptr = ft_strchr(line, 'S')) &&
								((filling_struct_sprite(ptr, map, line) != 0) ||
						(filling_struct_south_texture(ptr, map, line) != 0)))
		return (3);
	if ((ptr = ft_strchr(line, 'E')) &&
							(filling_struct_east_texture(ptr, map, line) != 0))
		return (3);
	if ((ptr = ft_strchr(line, 'W')) &&
							(filling_struct_west_texture(ptr, map, line) != 0))
		return (3);
	return (0);
}
