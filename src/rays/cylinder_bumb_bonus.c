/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bumb_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:08:52 by bduval            #+#    #+#             */
/*   Updated: 2025/06/20 10:03:43 by bduval           ###   ########.fr       */
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
t_vector get_local_cordinates(t_point p, t_vector z, t_point o)
{
	t_vector	u;
	t_vector	v;
	t_vector	cp;

	u = get_non_linear(z);
	u = v_unit(v_cross(u, z));
	v = v_unit(v_cross(u, z));
	cp = v_substract(p, o);
	p.x = v_dot(cp, u);
	p.y = v_dot(cp, v);
	p.z = v_dot(cp, z);
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
	normal = v_add(normal, v_scale(tangeant, modifyer.x));
	normal = v_add(normal, v_scale(bitangeant, modifyer.y));
	return (v_unit(normal));
}

t_vector	cylinder_bump(t_ray *ray)
{
	t_point	p_loc;
	t_point	p_rad;
	t_vector	modifyer;

	ray->normal = cylinder_normal(ray);
	p_loc = get_local_cordinates(ray->start, ray->impact_object->orientation,
			ray->impact_object->pos);
	if (fabs(proj_on_axis(ray->impact_object, ray->start)) < ray->impact_object->height / 2.0 - EPSLN)
	{
		p_rad.x = 0.5 + (atan2f(p_loc.y, p_loc.x) / (2 * M_PI));
		p_rad.y = (p_loc.z + ray->impact_object->height / 2.0) / ray->impact_object->height;
		p_rad.z = 0;
		modifyer = get_bump_vector(&ray->impact_object->bump, p_rad);
		ray->normal = add_in_tbn(ray->normal, modifyer);
	}
	else
	{
		//caps
	}
	return (ray->normal);
}
