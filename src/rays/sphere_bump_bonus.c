/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bump_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:08:52 by bduval            #+#    #+#             */
/*   Updated: 2025/06/23 11:52:16 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	get_sphere_coordinates(t_point p, t_obj *obj)
{
	t_vector		uv;
	static t_img	*last_bump;
	static t_vector	scaler;

	if (!last_bump || last_bump != obj->bump)
	{
		last_bump = obj->bump;
		scaler.x = 2 * M_PI * obj->radius;
		scaler.y = scaler.x;
	}
	uv.x = 0.5 + atan2f(p.z, p.x) / (2 * M_PI);
	uv.y = acosf(p.y / obj->radius) / M_PI;
	uv.x *= scaler.x;
	uv.y *= scaler.y;
	return (uv);
}

t_vector	sphere_bump(t_ray *ray)
{
	t_point		p_loc;
	t_vector	modifyer;
	t_vector	up;

	ft_bzero(&up, sizeof(t_vector));
	up.y = 1;
	ray->normal = sphere_normal(ray);
	p_loc = get_local_cordinates(ray->start, up,
			ray->impact_object->pos);
	p_loc = get_sphere_coordinates(p_loc, ray->impact_object);
	modifyer = get_bump_vector(ray->impact_object->bump, p_loc);
	ray->normal = add_in_tbn(ray->normal, modifyer);
	return (ray->normal);
}
