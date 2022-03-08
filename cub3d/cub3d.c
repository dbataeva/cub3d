/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:11:21 by cchromos          #+#    #+#             */
/*   Updated: 2021/01/20 11:11:24 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		if_error(int number)
{
	if (number == 1)
		write(2, "Error\nError of number of arguments\n", 35);
	else if (number == 2)
		write(2, "Error\nError of opening\n", 23);
	else if (number == 3)
		write(2, "Error\nError of configurations or map\n", 37);
	else if (number == 4)
		write(2, "Error\nError of memory\n", 22);
	else if (number == 5)
		write(2, "Error\nError of image\n", 21);
	else if (number == 6)
		write(2, "Error\nError of second argument\n", 31);
	else if (number == 7)
		write(2, "Error\nError of first argument\n", 30);
	return (0);
}

int		check_numbers_of_strings(int fd)
{
	char	*ptr;
	char	buf[1024];
	int		n;
	int		rd;

	n = 1;
	while ((rd = read(fd, buf, 1023)) > 0)
	{
		buf[rd] = '\0';
		ptr = buf;
		while ((ptr = ft_strchr(ptr, '\n')))
		{
			ptr++;
			n++;
		}
	}
	if (rd < 0)
	{
		write(2, "Error\nError of reading\n", 23);
		return (-1);
	}
	return (n);
}

int		check_argvs(int argc, char **argv, int *flag_save)
{
	int len;

	if ((argc != 2) && (argc != 3))
		return (1);
	if (argc == 3)
	{
		if ((argv[2][0] != '-') || (argv[2][1] != '-') || (argv[2][2] != 's') ||
			(argv[2][3] != 'a') || (argv[2][4] != 'v') || (argv[2][5] != 'e') ||
														(argv[2][6] != '\0'))
			return (6);
		*flag_save = 1;
	}
	len = ft_strlen(argv[1]) - 1;
	if ((argv[1][len] != 'b') || (argv[1][len - 1] != 'u') ||
						(argv[1][len - 2] != 'c') || (argv[1][len - 3] != '.'))
		return (7);
	return (0);
}

int		main(int argc, char **argv)
{
	int fd;
	int n;
	int flag_save;

	flag_save = 0;
	if ((n = check_argvs(argc, argv, &flag_save)) != 0)
		return (if_error(n));
	fd = open(argv[1], O_RDONLY);
	if (fd < 1)
		return (if_error(2));
	if (((n = check_numbers_of_strings(fd)) < 11) && (n != -1))
	{
		close(fd);
		return (if_error(3));
	}
	if (n == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if ((n = filling_lines(n, fd, flag_save)) != 0)
		return (if_error(n));
	return (0);
}
