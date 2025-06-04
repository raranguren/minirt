/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:23:25 by bduval            #+#    #+#             */
/*   Updated: 2025/06/04 09:01:54 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	c_normalize(t_color c)
{
	c.a /= 255;
	c.r /= 255;
	c.g /= 255;
	c.b /= 255;
	return (c);
}

t_color	c_set(float set)
{
	t_color	c;

	c.a = set;
	c.r = set;
	c.g = set;
	c.b = set;
	return (c);
}

t_color	c_multiply(t_color c, t_color scale)
{
	c.a = c.a * scale.a;
	c.r = c.r * scale.r;
	c.g = c.g * scale.g;
	c.b = c.b * scale.b;
	return (c);
}

t_color	c_scale(t_color c, float scale)
{
	c.a = c.a * scale;
	c.r = c.r * scale;
	c.g = c.g * scale;
	c.b = c.b * scale;
	return (c);
}
