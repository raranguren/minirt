/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 07:19:18 by bduval            #+#    #+#             */
/*   Updated: 2025/05/31 14:35:37 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_get_color(t_obj *obj, char **param)
{
	obj->color.a = 1;
	obj->color.r = ft_atoi(param[0]);
	obj->color.g = ft_atoi(param[1]);
	obj->color.b = ft_atoi(param[2]);
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
