/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_ceiling_floor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:11:28 by cchromos          #+#    #+#             */
/*   Updated: 2021/03/06 18:11:30 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		continue_of_continuing_floor(char *ptr, t_map_list *map)
{
	if (((*ptr == ' ') || (*ptr == '\0')) && (*(ptr - 1) == '0'))
		map->floor_b = 0;
	else if ((!((*ptr >= '1') && (*ptr <= '9')) && (*ptr != '-') &&
									(*(ptr + 1) != 0)) || (map->floor_b != -1))
		return (3);
	else
		map->floor_b = ft_atoi(ptr);
	if (*ptr == '-')
		ptr++;
	while ((*ptr >= '0') && (*ptr <= '9'))
		ptr++;
	while (*ptr == ' ')
		ptr++;
	if (*ptr == '\0')
		return (0);
	return (3);
}

int		continue_floor(char *ptr, t_map_list *map)
{
	while (*ptr == ' ')
		ptr++;
	while (*ptr == '0')
		ptr++;
	if ((*ptr == ',') && (*(ptr - 1) == '0'))
		map->floor_g = 0;
	else if ((!((*ptr >= '1') && (*ptr <= '9')) && (*ptr != '-') &&
									(*(ptr + 1) != 0)) || (map->floor_g != -1))
		return (3);
	else
		map->floor_g = ft_atoi(ptr);
	if (*ptr == '-')
		ptr++;
	while ((*ptr >= '0') && (*ptr <= '9'))
		ptr++;
	while (*ptr == ' ')
		ptr++;
	if (*(ptr++) != ',')
		return (3);
	while (*ptr == ' ')
		ptr++;
	while (*ptr == '0')
		ptr++;
	return (continue_of_continuing_floor(ptr, map));
}

int		continue_of_continuing_ceiling(char *ptr, t_map_list *map)
{
	if (((*ptr == ' ') || (*ptr == '\0')) && (*(ptr - 1) == '0'))
		map->ceiling_b = 0;
	else if ((!((*ptr >= '1') && (*ptr <= '9')) && (*ptr != '-') &&
								(*(ptr + 1) != 0)) || (map->ceiling_b != -1))
		return (3);
	else
		map->ceiling_b = ft_atoi(ptr);
	if (*ptr == '-')
		ptr++;
	while ((*ptr >= '0') && (*ptr <= '9'))
		ptr++;
	while (*ptr == ' ')
		ptr++;
	if (*ptr == '\0')
		return (0);
	return (3);
}

int		continue_ceiling(char *ptr, t_map_list *map)
{
	while (*ptr == ' ')
		ptr++;
	while (*ptr == '0')
		ptr++;
	if ((*ptr == ',') && (*(ptr - 1) == '0'))
		map->ceiling_g = 0;
	else if ((!((*ptr >= '1') && (*ptr <= '9')) && (*ptr != '-') &&
								(*(ptr + 1) != 0)) || (map->ceiling_g != -1))
		return (3);
	else
		map->ceiling_g = ft_atoi(ptr);
	if (*ptr == '-')
		ptr++;
	while ((*ptr >= '0') && (*ptr <= '9'))
		ptr++;
	while (*ptr == ' ')
		ptr++;
	if (*(ptr++) != ',')
		return (3);
	while (*ptr == ' ')
		ptr++;
	while (*ptr == '0')
		ptr++;
	return (continue_of_continuing_ceiling(ptr, map));
}

int		check_other_symbols(t_map_list *map, char **line)
{
	int i;
	int j;

	i = 0;
	while (i < map->first_line_of_map)
	{
		j = 0;
		while (line[i][j] == ' ')
			j++;
		if ((line[i][j] != 'R') && (line[i][j] != 'N') && (line[i][j] != 'S')
		&& (line[i][j] != 'E') && (line[i][j] != 'W') && (line[i][j] != 'F')
		&& (line[i][j] != 'C') && (line[i][j] != '\0'))
			return (3);
		i++;
	}
	return (0);
}
