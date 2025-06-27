/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:29:20 by bduval            #+#    #+#             */
/*   Updated: 2025/06/27 16:21:52 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	get_non_linear(t_vector v)
{
	t_vector	res;

	if (fabs(v.x) > fabs(v.z))
	{
		res.x = 0;
		res.y = 0;
		res.z = 1;
	}
	else
	{
		res.x = 1;
		res.y = 0;
		res.z = 0;
	}
	return (res);
}

/*Return local coordinates of p depending on z unit vector bind to z axis*/
t_vector	get_local_cordinates(t_point p, t_vector k, t_point o)
{
	t_vector	i;
	t_vector	j;
	t_vector	cp;

	i = get_non_linear(k);
	i = v_unit(v_cross(i, k));
	j = v_unit(v_cross(i, k));
	cp = v_substract(p, o);
	p.x = v_dot(cp, i);
	p.y = v_dot(cp, j);
	p.z = v_dot(cp, k);
	return (p);
}

t_vector	add_in_tbn(t_vector normal, t_vector modifyer)
{
	t_vector	tangeant;
	t_vector	bitangeant;

	tangeant = get_non_linear(normal);
	tangeant = v_unit(v_cross(normal, tangeant));
	bitangeant = v_unit(v_cross(tangeant, normal));
	normal = v_add(normal, v_scale(bitangeant, modifyer.x));
	normal = v_add(normal, v_scale(tangeant, modifyer.y));
	return (v_unit(normal));
}

static int	get_pixel_value(t_img *img, unsigned int x, unsigned int y)
{
	char	*p;

	x = x % img->width;
	y = y % img->height;
	p = img->data + (y * img->size_line + x * (img->bpp / 8));
	return ((unsigned char)*p);
}

/*
 Return the tangeant and bitangeant of the normal factors
 p :  x, y coordinates [-1:1]
*/
t_vector	get_bump_vector(t_img *bump, t_point p)
{
	int	height;
	int	height_x;
	int	height_y;

	p = v_scale(p, STEP_GRID);
	p.x *= bump->width;
	p.y *= bump->height;
	height_x = p.x - 1;
	height_y = p.y - 1;
	height = get_pixel_value(bump, p.x, p.y);
	height_x = get_pixel_value(bump, height_x, p.y);
	height_y = get_pixel_value(bump, p.x, height_y);
	p.x = height - height_x;
	p.y = height - height_y;
	p = v_scale(p, BUMP_STRENGTH);
	return (p);
}
