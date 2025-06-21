/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:29:20 by bduval            #+#    #+#             */
/*   Updated: 2025/06/21 09:43:32 by bduval           ###   ########.fr       */
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
	return (v_cross(res, v));
}

/*Return local coordinates of p depending on z unit vector bind to z axis*/
t_vector get_local_cordinates(t_point p, t_vector k, t_point o)
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

/*
TBN = | u.x  v.x  z.x |
      | u.y  v.y  z.y |
      | u.z  v.z  z.z |

where:

    t is the tangent vector (in world space).
    b is the bitangent vector (in world space).
    n is the normal vector (in world space).

return :
	the addition of 
*/
t_vector	add_in_tbn(t_vector normal, t_vector modifyer)
{
	t_vector	tangeant;
	t_vector	bitangeant;

	tangeant = get_non_linear(normal);
	tangeant = v_unit(v_cross(tangeant, normal));
	bitangeant = v_unit(v_cross(tangeant, normal));
	normal = v_add(normal, v_scale(bitangeant, modifyer.x));
	normal = v_add(normal, v_scale(tangeant, modifyer.y));
	return (v_unit(normal));
}

static char	get_pixel_value(t_img *img, unsigned int x, unsigned int y)
{
	char	*p;

	p = img->data +
		(y * img->size_line + x * (img->bpp / 8));
	
	return (*p);
}

/*
 Return the tangeant and bitangeant of the normal factors
 p :  x, y coordinates [-1:1]
 */
t_vector	get_bump_vector(t_bump *bump, t_point p)
{
	float	height;
	float	height_x;
	float	height_y;
	float	step;

	step = 1;
	p.x = (int)p.x % bump->width;
	p.y = (int)p.y % bump->height;
	
	height_x = p.x + step;
	height_y = p.y + step;

	height = get_pixel_value(bump->map.id, p.x, p.y);
	height_x = get_pixel_value(bump->map.id, height_x, p.y);
	height_y = get_pixel_value(bump->map.id, p.x, height_y);
	
	p.x = ((float)height - height_x) / step;
	p.y = ((float)height - height_y) / step;
	p = v_scale(p, BUMP_STRENGTH);
	return (p);
}
