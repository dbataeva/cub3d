/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:31:14 by cchromos          #+#    #+#             */
/*   Updated: 2021/01/22 20:31:17 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		str_to_array(char **line, int max_len)
{
	int		i;
	int		len;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(*line);
	while (*(*line + j))
	{
		if (*(*line + j) == ' ')
			*(*line + j) = '1';
		j++;
	}
	if (len != max_len)
		i = new_line(line, max_len);
	return (i);
}

int		map_2d(char **line, t_map_list *map, t_player_list *player)
{
	int i;

	i = map->first_line_of_map;
	map->map_array = &line[map->first_line_of_map];
	while (line[i])
	{
		if (ft_strchr(line[i], 'N'))
			is_player_here(line[i], 'N', player, i);
		if (ft_strchr(line[i], 'S'))
			is_player_here(line[i], 'S', player, i);
		if (ft_strchr(line[i], 'E'))
			is_player_here(line[i], 'E', player, i);
		if (ft_strchr(line[i], 'W'))
			is_player_here(line[i], 'W', player, i);
		i++;
	}
	player->x_player = player->x_player - map->first_line_of_map;
	if ((player->count_of_players != 1) ||
			((i = flood_fill(player, map, &line[map->first_line_of_map])) != 0))
		return (3);
	return (check_other_symbols(map, line));
}

int		check_two_map(char **line, int i)
{
	int j;

	while (i >= 0)
	{
		j = 0;
		while (line[i][j] == ' ')
			j++;
		if ((line[i][j] == '1') || (line[i][j] == '0') ||
					(line[i][j] == '2'))
			return (3);
		else
			i--;
	}
	return (0);
}

int		map_to_array(char **line, t_map_list *map, t_player_list *player)
{
	int i;
	int	result;

	count_len_of_str_in_array(map, line);
	i = 0;
	while (i < map->first_line_of_map)
	{
		if ((result = filling_struct(line[i], map)) != 0)
			return (result);
		i++;
	}
	if (check_two_map(line, map->first_line_of_map - 1) != 0)
		return (3);
	map->count_of_str_in_array = map->last_line_of_map -
													map->first_line_of_map + 1;
	i = map->first_line_of_map;
	while (i <= map->last_line_of_map)
	{
		if ((result = str_to_array(&line[i], map->len_of_str_in_array)) != 0)
			return (result);
		i++;
	}
	if ((i = check_struct(map)) == 0)
		i = map_2d(line, map, player);
	return (i);
}

int		copy_map(char **line, t_map_list *map, t_player_list *player)
{
	int i;

	i = 0;
	while (line[i])
		i++;
	i--;
	while (!ft_strchr(line[i], '1') && !ft_strchr(line[i], '0') &&
										!ft_strchr(line[i], '2') && (i >= 0))
		i--;
	map->last_line_of_map = i;
	if ((i = map_to_array(line, map, player)) != 0)
	{
		if (i == -1)
			return (4);
		else
			return (i);
	}
	return (0);
}
