/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:04:09 by bduval            #+#    #+#             */
/*   Updated: 2025/05/21 20:27:42 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_valid_double(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
		str++;
	if (*str == '\0')
		return (1);
	if (*str != '.')
		return (0);
	str++;
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
		str++;
	return (*str == '\0');
}

static double	ft_strtod(char *str)
{
	double	num;
	double	decimal;
	double	sign;

	num = 0;
	sign = 1;
	decimal = 1;
	while (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign *= -1;
	while (ft_isdigit(*str))
		num = num * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			decimal *= 0.1;
			num += (*str++ - '0') * decimal;
		}
	}
	return (num * sign);
}

int	ft_atoi_double(double *res, char *str)
{
	while (ft_isspace(*str))
		str++;
	if (!is_valid_double(str))
		return (1);
	*res = ft_strtod(str);
	if (isinf(*res) || *res > HUGE_VAL)
		return (1);
	return (0);
}

/*
int	main(int argc, char **argv)
{
	double	n;
	for (int i = 1; i < argc; i++)
	{
		int err = ft_atoi_double(&n, argv[i]);
		printf("argv[%i] err=%i  n=%.20f\n", i, err, n);
		n = strtod(argv[1], NULL);
		printf("argv[%i] target n=%.20f\n", i, n);
	}
}
*/
