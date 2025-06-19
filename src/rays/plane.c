/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:56:14 by bduval            #+#    #+#             */
/*   Updated: 2025/06/16 19:58:06 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	plane_normal(t_ray *ray)
{
	t_vector	normal;
	t_obj		*obj;

	obj = ray->impact_object;
	normal = v_unit(obj->orientation);
	if (v_dot(ray->direction, normal) > 0)
		normal = v_scale(normal, -1);
	return (normal);
}

float	plane_colision_dist(t_obj *plane, t_ray *ray)
{
	float	dot;

	dot = v_dot(ray->direction, plane->orientation);
	if (!dot)
		return (-1);
	return  (-v_dot(
			v_substract(ray->start, plane->pos), plane->orientation) / dot);
}

int	plane_collision(t_obj *plane, t_ray *ray)
{
	float	dist;

	dist = plane_colision_dist(plane, ray);
	if (dist < EPSLN || dist > ray->shortest_impact_dist - EPSLN)
		return (0);
	if (!ray->from_cam)
		return (1);
	ray->shortest_impact_dist = dist;
	ray->impact_object = plane;
	return (1);
}
