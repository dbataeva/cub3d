/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:57:54 by cchromos          #+#    #+#             */
/*   Updated: 2021/02/04 16:57:56 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		how_much_sprites(char **map)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int		check_array(char **array, int last_line, t_map_list *map)
{
	int i;
	int j;

	i = 0;
	map->num_sprites = how_much_sprites(array);
	while (array[i] && (i <= last_line))
	{
		j = 0;
		while (array[i][j])
		{
			if ((array[i][j] == '0') || (array[i][j] == '1') ||
			(array[i][j] == '2') || (array[i][j] == 'N') || (array[i][j] == 'S')
			|| (array[i][j] == 'E') || (array[i][j] == 'W') ||
														(array[i][j] == ' '))
				j++;
			else
				return (3);
		}
		i++;
	}
	return (0);
}

int		searching_nsew(char *line)
{
	char *ptr;

	if ((ptr = ft_strchr(line, 'N')))
		ptr++;
	else if ((ptr = ft_strchr(line, 'S')))
		ptr++;
	else if ((ptr = ft_strchr(line, 'E')))
		ptr++;
	else if ((ptr = ft_strchr(line, 'W')))
		ptr++;
	if (ptr && ((*ptr == '2') || (*ptr == '0') || (*ptr == '1')))
		return (1);
	if (!ptr)
		return (1);
	return (0);
}

void	count_len_of_str_in_array(t_map_list *map, char **line)
{
	int i;
	int j;
	int len_of_str_in_array;

	i = map->last_line_of_map;
	j = 0;
	while ((ft_strchr(line[i], '1') || ft_strchr(line[i], '0') ||
			ft_strchr(line[i], '0') || (line[i][0] == ' ')) &&
			!ft_strchr(line[i], 'R') && !ft_strchr(line[i], 'F') &&
			!ft_strchr(line[i], 'C') && searching_nsew(line[i]))
	{
		len_of_str_in_array = ft_strlen(line[i]);
		if (len_of_str_in_array > j)
			j = len_of_str_in_array;
		i--;
	}
	map->len_of_str_in_array = j;
	map->first_line_of_map = i + 1;
	return ;
}

void	is_player_here(char *line, char chr, t_player_list *player, int i)
{
	int j;

	j = 0;
	while (line[j] != chr)
		j++;
	player->count_of_players++;
	player->vector_of_player = chr;
	player->x_player = i;
	player->y_player = j;
	return ;
}
