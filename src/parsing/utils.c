/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 07:19:18 by bduval            #+#    #+#             */
/*   Updated: 2025/05/29 00:25:35 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_get_color(int *dest, char **param)
{
	int		i;
	char	*color;

	color = (char *)dest;
	i = 3;
	while (i >= 0)
	{
		if (param[i])
			color[i] = ft_atoi(param[i]);
		else
			color[i] = 0;
		i--;
	}
	return (0);
}

int	is_normalized(double n)
{
	if (n < -1 || n > 1)
		return (0);
	return (1);
}

int	ft_is_double(const char *str)
{
	while (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
		str++;
	if (*str != '.')
		return (1);
	str++;
	if (!ft_isdigit(*str))
		return (0);
	return (1);
}

int	ft_is_char(const char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	if (len > 3)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (len == 3 && str[i] > STR_CHAR_MAX[i])
			return (0);
		i++;
	}
	return (1);
}
