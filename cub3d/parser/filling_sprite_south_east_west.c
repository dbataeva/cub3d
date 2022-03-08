/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_sprite_south_east_west.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:43:07 by cchromos          #+#    #+#             */
/*   Updated: 2021/01/22 20:43:09 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		filling_struct_sprite(char *ptr, t_map_list *map, char *line)
{
	char	*check;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] != 'S')
		return (3);
	if ((ptr[1] != ' ') && (ptr[1] != 'O'))
		return (3);
	if (*(++ptr) == 'O')
		return (0);
	if (map->sprite)
		return (3);
	if (*ptr)
		ptr++;
	else
		return (0);
	while (*ptr == ' ')
		ptr++;
	if ((check = ft_strnstr(ptr, ".xpm", ft_strlen(ptr))))
		return (writing_path_sprite(check, ptr, map));
	return (3);
}

int		filling_struct_south_texture(char *ptr, t_map_list *map, char *line)
{
	char	*check;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] != 'S')
		return (3);
	if (*(++ptr) != 'O')
		return (0);
	if (map->south)
		return (3);
	ptr++;
	while (*ptr == ' ')
		ptr++;
	if ((check = ft_strnstr(ptr, ".xpm", ft_strlen(ptr))))
		return (writing_path_south(check, ptr, map));
	return (3);
}

int		filling_struct_east_texture(char *ptr, t_map_list *map, char *line)
{
	char	*check;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if ((line[i] != 'E') && (line[i] != 'W'))
		return (3);
	if (line[i] == 'W')
		return (0);
	if ((line[i] != 'W') && (*(++ptr) != 'A'))
		return (3);
	if (map->east)
		return (3);
	ptr++;
	while (*ptr == ' ')
		ptr++;
	if ((check = ft_strnstr(ptr, ".xpm", ft_strlen(ptr))))
		return (writing_path_east(check, ptr, map));
	return (3);
}

int		filling_struct_west_texture(char *ptr, t_map_list *map, char *line)
{
	char	*check;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] != 'W')
		return (3);
	if (map->west)
		return (3);
	if (*(++ptr) != 'E')
		return (3);
	ptr++;
	while (*ptr == ' ')
		ptr++;
	if ((check = ft_strnstr(ptr, ".xpm", ft_strlen(ptr))))
		return (writing_path_west(check, ptr, map));
	return (3);
}

int		new_line(char **line, int max_len)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!(tmp = ft_calloc(max_len + 1, 1)))
		return (4);
	while (*(*line + i))
	{
		tmp[i] = (*(*line + i));
		i++;
	}
	while (i < max_len)
	{
		tmp[i] = ' ';
		i++;
	}
	free(*line);
	*line = tmp;
	return (0);
}
