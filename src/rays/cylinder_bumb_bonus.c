/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bumb_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:08:52 by bduval            #+#    #+#             */
/*   Updated: 2025/06/20 12:28:29 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	get_cyl_radial_coordinates(t_point p, t_obj *obj)
{
	t_vector uv;

	uv.x = 0.5 + atan2f(p.y, p.x) / (2.0 * M_PI);
	uv.y = (p.z + obj->height / 2.0) / obj->height;
	uv.z = 0;
	return (uv);
}

t_vector	get_disc_coordinates(t_point p_loc, t_obj *obj)
{
	t_vector	uv;
	
	uv.x = p_loc.x / (2.0 * obj->radius) + 0.5;
	uv.y = p_loc.y / (2.0 * obj->radius) + 0.5;
	uv.z = 0;

	return (uv);
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
		p_rad = get_cyl_radial_coordinates(p_loc, ray->impact_object);
	else
		p_rad = get_disc_coordinates(p_loc, ray->impact_object);
	modifyer = get_bump_vector(&ray->impact_object->bump, p_rad);
	ray->normal = add_in_tbn(ray->normal, modifyer);
	return (ray->normal);
}
