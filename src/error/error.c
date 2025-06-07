/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:00:30 by bduval            #+#    #+#             */
/*   Updated: 2025/06/07 22:32:36 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	print_location(const char *file, int line, const char *func)
{
	write(2, "Error in file ", 14);
	write(2, file, ft_strlen(file));
	write(2, " line(", 6);
	ft_putnbr_fd(line, 2);
	write(2, ") : ", 4);
	if (func)
		write(2, func, ft_strlen(func));
	write(2, "\n", 1);
	return (0);
}

int	print_error2(
		char *err1, char *err2, const char *f, int l)
{
	print_location(f, l, NULL);
	write(2, err1, ft_strlen(err1));
	write(2, " : ", 3);
	write(2, err2, ft_strlen(err2));
	write(2, "\n", 1);
	return (1);
}

int	print_error(char *err, const char *file, int line, const char *func)
{
	print_location(file, line, func);
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
	return (1);
}

int	error(char *str)
{
	ft_putendl_fd("Error", 2);
	if (errno)
		perror(str);
	else
		ft_putendl_fd(str, 2);
	return (1);
}

int	error3(char *a, char *b, char *c)
{
	ft_putendl_fd("Error", 2);
	if (a)
		write(2, a, ft_strlen(a));
	if (b)
		write(2, b, ft_strlen(b));
	if (c)
		write(2, c, ft_strlen(c));
	write(2, "\n", 1);
	return (1);
}
