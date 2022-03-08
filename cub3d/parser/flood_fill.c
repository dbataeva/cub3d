/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:55:51 by cchromos          #+#    #+#             */
/*   Updated: 2021/01/22 20:55:53 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	filling(int i, int j, char **array, t_map_list *map)
{
	if ((array[i][j] == '1') || (array[i][j] == 'Z'))
		return ;
	array[i][j] = 'Z';
	if ((i - 1) >= 0)
		filling(i - 1, j, array, map);
	if ((i + 1) < map->count_of_str_in_array)
		filling(i + 1, j, array, map);
	if ((j - 1) >= 0)
		filling(i, j - 1, array, map);
	if ((j + 1) < map->len_of_str_in_array)
		filling(i, j + 1, array, map);
	return ;
}

int		return_0(char **array, t_player_list *player, t_map_list *map)
{
	int i;
	int j;

	i = 0;
	array[player->x_player][player->y_player] = player->vector_of_player;
	while (i < map->num_sprites)
	{
		array[map->sprite_on_map_x[i]][map->sprite_on_map_y[i]] = '2';
		i++;
	}
	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == 'Z')
				array[i][j] = '0';
			j++;
		}
		i++;
	}
	return (0);
}

int		where_are_sprites(char **array, t_map_list *map)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	if (!(map->sprite_on_map_x = (int *)malloc(sizeof(int) * map->num_sprites))
	|| !(map->sprite_on_map_y = (int *)malloc(sizeof(int) * map->num_sprites)))
		return (4);
	while (array[i] && (count < map->num_sprites))
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == '2')
			{
				map->sprite_on_map_x[count] = i;
				map->sprite_on_map_y[count] = j;
				count++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	filling_all_map(int i, int j, char **array, t_map_list *map)
{
	int x;
	int y;

	filling(i, j, array, map);
	x = 0;
	while (array[x])
	{
		y = 0;
		while (array[x][y] != '\0')
		{
			while ((array[x][y] == ' ') || (array[x][y] == '1') ||
														(array[x][y] == 'Z'))
				y++;
			if (array[x][y] != '\0')
				filling(x, y, array, map);
		}
		x++;
	}
	return ;
}

int		flood_fill(t_player_list *player, t_map_list *map, char **array)
{
	int i;

	if ((i = check_array(array, map->last_line_of_map, map)) != 0)
		return (i);
	if ((i = where_are_sprites(array, map)) != 0)
	{
		if (map->sprite_on_map_x)
			free(map->sprite_on_map_x);
		return (i);
	}
	filling_all_map(player->x_player, player->y_player, array, map);
	if (ft_strchr(array[0], 'Z') ||
	ft_strchr(array[map->count_of_str_in_array - 1], 'Z'))
		return (3);
	while ((array[i][0] != 'Z') && (i < map->count_of_str_in_array - 1))
		i++;
	if (array[i][0] == 'Z')
		return (3);
	i = 0;
	while ((array[i][map->len_of_str_in_array - 1] != 'Z')
	&& (i < map->count_of_str_in_array - 1))
		i++;
	if (array[i][map->len_of_str_in_array - 1] == 'Z')
		return (3);
	return (return_0(array, player, map));
}
