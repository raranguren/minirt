/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:57:27 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/15 17:55:14 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// precision fixed at 2 decimals
// does not print trailing zeroes
void	ft_putfloat_fd(float n, int fd)
{
	long	digits;
	int		decimals;

	digits = roundf(n * 100);
	if (digits < 0)
	{
		write(fd, "-", 1);
		digits = -digits;
	}
	ft_putnbr_fd(digits / 100, fd);
	decimals = digits % 100;
	if (!decimals)
		return ;
	write(fd, ".", 1);
	while (decimals % 10 == 0)
		decimals /= 10;
	ft_putnbr_fd(decimals, fd);
}
