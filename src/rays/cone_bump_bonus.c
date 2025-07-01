/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bump_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:08:52 by bduval            #+#    #+#             */
/*   Updated: 2025/07/01 12:21:01 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	get_cone_coordinates(t_point p, t_obj *obj)
{
	float		theta;
	t_vector	uv;

	theta = atan2f(p.y, p.x);
	if (theta < 0)
		theta += 2.0 * M_PI;
	uv.x = v_magnitude(p) / sqrt(obj->height * obj->height
			+ obj->radius * obj->radius);
	uv.y = 0.5 + theta / (2.0 * M_PI);
	return (uv);
}

t_vector	cone_bump(t_ray *ray)
{
	t_point		p_loc;
	t_vector	modifyer;

	ray->normal = cone_normal(ray);
	p_loc = get_local_cordinates(ray->start, ray->impact_object->orientation,
			ray->impact_object->pos);
	if (p_loc.z < ray->impact_object->height - EPSLN)
		p_loc = get_cone_coordinates(p_loc, ray->impact_object);
	else
		p_loc = get_disc_coordinates(p_loc, ray->impact_object);
	modifyer = get_bump_vector(ray->impact_object->bump, p_loc, STEP_GRID);
	ray->normal = add_in_tbn(ray->normal, modifyer);
	return (ray->normal);
}
