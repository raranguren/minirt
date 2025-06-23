/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bumb_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:08:52 by bduval            #+#    #+#             */
/*   Updated: 2025/06/23 14:27:40 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	get_cyl_radial_coordinates(t_point p, t_obj *obj)
{
	float		theta;
	t_vector	uv;

	theta = atan2f(p.y, p.x);
	uv.x = p.z + obj->height;
	uv.y = obj->radius * theta + M_PI * obj->radius;
	return (uv);
}

t_vector	get_disc_coordinates(t_point p_loc, t_obj *obj)
{
	t_vector	uv;
	
	uv.x = p_loc.x + obj->radius;
	uv.y = p_loc.y + obj->radius;
	uv.z = 0;
	print_vector("disc", uv);
	return (uv);
}
t_vector	cylinder_bump(t_ray *ray)
{
	t_point	p_loc;
	t_vector	modifyer;

	ray->normal = cylinder_normal(ray);
	p_loc = get_local_cordinates(ray->start, ray->impact_object->orientation,
			ray->impact_object->pos);
	if (fabs(proj_on_axis(ray->impact_object, ray->start)) < ray->impact_object->height / 2.0 - EPSLN)
		p_loc = get_cyl_radial_coordinates(p_loc, ray->impact_object);
	else
		p_loc = get_disc_coordinates(p_loc, ray->impact_object);
	modifyer = get_bump_vector(ray->impact_object->bump, p_loc);
	ray->normal = add_in_tbn(ray->normal, modifyer);
	return (ray->normal);
}
