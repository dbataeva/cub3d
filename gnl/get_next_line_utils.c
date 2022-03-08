/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 18:55:28 by cchromos          #+#    #+#             */
/*   Updated: 2020/12/07 18:55:36 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

char		*ft_strchr(const char *str, int ch)
{
	unsigned char	character;
	int				i;

	i = 0;
	character = (unsigned char)ch;
	while (str[i] != '\0')
	{
		if (str[i] == character)
			return ((char *)str + i);
		else
			i++;
	}
	if (character == '\0')
		return ((char *)str + ft_strlen(str));
	return (NULL);
}

void		ft_bzero(void *s, size_t n)
{
	unsigned char *c;

	c = (unsigned char *)s;
	while (n)
	{
		c[n - 1] = '\0';
		n--;
	}
	return ;
}

void		*ft_calloc(size_t num, size_t size)
{
	void	*mem;

	mem = malloc(num * size);
	if (mem == 0)
		return (NULL);
	ft_bzero(mem, num * size);
	return (mem);
}

void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*destination;
	const unsigned char	*source;

	if (dest == src)
		return (dest);
	destination = (unsigned char *)dest;
	source = (unsigned char *)src;
	while (n)
	{
		destination[n - 1] = source[n - 1];
		n--;
	}
	return (dest);
}
