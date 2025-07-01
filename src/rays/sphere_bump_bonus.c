/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bump_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:08:52 by bduval            #+#    #+#             */
/*   Updated: 2025/07/01 12:30:33 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	get_sphere_coordinates(t_point p)
{
	t_vector		uv;

	p = v_unit(p);
	uv.x = 0.5f + (atan2f(p.z, p.x) / (2.0f * M_PI));
	uv.y = acosf(p.y) / M_PI;
	return (uv);
}

t_vector	sphere_bump(t_ray *ray)
{
	t_point		p_loc;
	t_vector	modifyer;

	ray->normal = sphere_normal(ray);
	p_loc = v_substract(ray->start, ray->impact_object->pos);
	p_loc = get_sphere_coordinates(p_loc);
	modifyer = get_bump_vector(ray->impact_object->bump, p_loc, 1.0f);
	ray->normal = add_in_tbn(ray->normal, modifyer);
	return (ray->normal);
}
