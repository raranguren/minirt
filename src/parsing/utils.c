/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 07:19:18 by bduval            #+#    #+#             */
/*   Updated: 2025/06/18 00:18:09 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_get_color(t_obj *obj, char **param)
{
	obj->color.a = 1;
	if (!BONUS && (obj->type == LIGHT || obj->type == AMB_LIGHT))
	{
		obj->color.r = 255;
		obj->color.g = 255;
		obj->color.b = 255;
	}
	else
	{
		obj->color.r = ft_atoi(param[0]);
		obj->color.g = ft_atoi(param[1]);
		obj->color.b = ft_atoi(param[2]);
	}
	obj->color.r *= 1.0;
	obj->color.g *= 1.0;
	obj->color.b *= 1.0;
	return (0);
}

int	is_normalized(float n)
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
		i++;
	}
	if (len == 3 && ft_strncmp(str, "255", 3) > 0)
		return (0);
	return (1);
}
