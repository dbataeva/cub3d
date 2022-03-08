/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:26:43 by cchromos          #+#    #+#             */
/*   Updated: 2021/03/06 18:26:47 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		writing_path_sprite(char *check, char *ptr, t_map_list *map)
{
	int i;

	i = 4;
	while (check[i] == ' ')
		i++;
	if (check[i] == '\0')
		check[4] = '\0';
	if ((i = open(ptr, O_RDONLY)) != -1)
	{
		close(i);
		if (!map->sprite)
			map->sprite = ptr;
		else
			return (3);
	}
	else
		return (3);
	return (0);
}

int		writing_path_south(char *check, char *ptr, t_map_list *map)
{
	int i;

	i = 4;
	while (check[i] == ' ')
		i++;
	if (check[i] == '\0')
		check[4] = '\0';
	if ((i = open(ptr, O_RDONLY)) != -1)
	{
		close(i);
		if (!map->south)
			map->south = ptr;
		else
			return (3);
	}
	else
		return (3);
	return (0);
}

int		writing_path_east(char *check, char *ptr, t_map_list *map)
{
	int i;

	i = 4;
	while (check[i] == ' ')
		i++;
	if (check[i] == '\0')
		check[4] = '\0';
	if ((i = open(ptr, O_RDONLY)) != -1)
	{
		close(i);
		if (!map->east)
			map->east = ptr;
		else
			return (3);
	}
	else
		return (3);
	return (0);
}

int		writing_path_west(char *check, char *ptr, t_map_list *map)
{
	int i;

	i = 4;
	while (check[i] == ' ')
		i++;
	if (check[i] == '\0')
		check[4] = '\0';
	if ((i = open(ptr, O_RDONLY)) != -1)
	{
		close(i);
		if (!map->west)
			map->west = ptr;
		else
			return (3);
	}
	else
		return (3);
	return (0);
}

int		writing_path_north(char *check, char *ptr, t_map_list *map)
{
	int i;

	i = 4;
	while (check[i] == ' ')
		i++;
	if (check[i] == '\0')
		check[4] = '\0';
	if ((i = open(ptr, O_RDONLY)) != -1)
	{
		close(i);
		if (!map->north)
			map->north = ptr;
		else
			return (3);
	}
	else
		return (3);
	return (0);
}
