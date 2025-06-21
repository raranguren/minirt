
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bumb_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:08:52 by bduval            #+#    #+#             */
/*   Updated: 2025/06/20 21:44:24 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	get_sphere_coordinates(t_point p, t_obj *obj)
{
	float		theta;
	float		phi;
	t_vector	uv;

	theta = atan2f(p.z, p.x);
	phi = acosf(p.y / obj->radius);

	uv.x = 0.5 + theta / (2 * M_PI);
	uv.y = phi / M_PI;
	uv.x *= obj->bump.width;
	uv.y *= obj->bump.height;
	return (uv);
}

t_vector	sphere_bump(t_ray *ray)
{
	t_point	p_loc;
	t_vector	modifyer;

	ray->normal = cylinder_normal(ray);
	p_loc = get_local_cordinates(ray->start, ray->normal,
			ray->impact_object->pos);
	p_loc = get_sphere_coordinates(p_loc, ray->impact_object);
	modifyer = get_bump_vector(&ray->impact_object->bump, p_loc);
	ray->normal = add_in_tbn(ray->normal, modifyer);
	return (ray->normal);
}
