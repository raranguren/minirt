/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:23:25 by bduval            #+#    #+#             */
/*   Updated: 2025/06/04 17:14:15 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	c_range(t_color c)
{
	c.a = fmin(fmax(c.a, 0), 255);
	c.r = fmin(fmax(c.r, 0), 255);
	c.g = fmin(fmax(c.g, 0), 255);
	c.b = fmin(fmax(c.b, 0), 255);
	return (c);
}

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

t_color	c_add(t_color c, t_color c2)
{
	c.a = c.a + c2.a;
	c.r = c.r + c2.r;
	c.g = c.g + c2.g;
	c.b = c.b + c2.b;
	return (c_range(c));
}

t_color	c_multiply(t_color c, t_color scale)
{
	c.a = c.a * scale.a;
	c.r = c.r * scale.r;
	c.g = c.g * scale.g;
	c.b = c.b * scale.b;
	return (c_range(c));
}
