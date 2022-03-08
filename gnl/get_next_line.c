/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 18:54:31 by cchromos          #+#    #+#             */
/*   Updated: 2020/12/07 18:54:34 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		rest_check_n(char **rest, char **line)
{
	char *tmp;
	char *ptr;

	ptr = ft_strchr(*rest, '\n');
	*ptr = '\0';
	ptr++;
	if (!(*line = ft_calloc(ft_strlen(*rest) + 1, 1)))
	{
		free(*rest);
		return (-1);
	}
	*line = ft_memcpy(*line, *rest, ft_strlen(*rest));
	if (!(tmp = ft_calloc(ft_strlen(ptr) + 1, 1)))
	{
		free(*rest);
		free(*line);
		return (-1);
	}
	tmp = ft_memcpy(tmp, ptr, ft_strlen(ptr));
	free(*rest);
	*rest = tmp;
	return (1);
}

int		rest_check(char **rest, char **line)
{
	if (!(*line = ft_calloc(ft_strlen(*rest) + 1, 1)))
	{
		free(*rest);
		return (-1);
	}
	*line = ft_memcpy(*line, *rest, ft_strlen(*rest));
	free(*rest);
	*rest = NULL;
	return (0);
}

int		new_rest(char **rest, char *buf, int rd)
{
	char *tmp;

	if (!(tmp = ft_calloc((rd + 1 + ft_strlen(*rest)), 1)))
	{
		free(*rest);
		return (-1);
	}
	tmp = ft_memcpy(tmp, *rest, ft_strlen(*rest));
	ft_memcpy(tmp + ft_strlen(*rest), buf, rd);
	free(*rest);
	*rest = tmp;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*rest;
	int			rd;
	char		buf[BUFFER_SIZE + 1];

	if ((!line) || (fd < 0) || (BUFFER_SIZE < 1) || (fd > 10240))
		return (-1);
	while (((rd = read(fd, buf, BUFFER_SIZE)) >= 0))
	{
		if (!rest)
		{
			if (!(rest = ft_calloc(1, 1)))
				return (-1);
		}
		if ((new_rest(&rest, buf, rd) == -1))
			return (-1);
		if (ft_strchr(rest, '\n'))
			return (rest_check_n(&rest, line));
		if ((rd < BUFFER_SIZE) && !(ft_strchr(rest, '\n')))
			return (rest_check(&rest, line));
	}
	return (-1);
}
