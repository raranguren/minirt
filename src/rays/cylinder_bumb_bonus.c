/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bumb_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:08:52 by bduval            #+#    #+#             */
/*   Updated: 2025/06/18 15:11:58 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	get_non_linear(t_vector v)
{
	t_vector	res;
	if (v.x)
	{
		res.x = 0;
		res.y = 1;
		res.z = 0;
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
*/
t_vector	get_world_coordinates(t_point p, t_vector z)
{
	t_vector	u;
	t_vector	v;
	t_vector	w_p;

	u = get_non_linear(z);
	u = v_unit(v_cross(u, z));
	v = v_unit(v_cross(u, z));
	w_p.x = (u.x * p.x) + (v.x * p.y) + (z.x * p.z);
	w_p.y = (u.y * p.x) + (v.y * p.y) + (z.y * p.z);
	w_p.z = (u.z * p.x) + (v.z * p.y) + (z.z * p.z);
	return (w_p);
}

t_vector	cylinder_bump(t_ray *ray)
{
	t_point	p;
	float	u;
	float	v;
	t_vector	modifyer;

	ray->normal = cylinder_normal(ray);
	p = get_local_cordinates(ray->start, ray->impact_object->orientation,
			ray->impact_object->pos);
	if (fabs(proj_on_axis(ray->impact_object, ray->start)) > ray->impact_object->height / 2.0 - EPSLN)
	{
		u = 0.5 + (atan2f(p.y, p.x) / (2 * M_PI));
		v = (p.z + ray->impact_object->height / 2.0) / ray->impact_object->height;
		modifyer = get_bump_vector(&ray->impact_object->bump, u, v);
		modifyer = get_world_coordinates(modifyer, ray->normal);
		ray->normal = v_unit(v_add(ray->normal, modifyer));
	}
	else
	{
		//caps
	}
	return (ray->normal);
}
