/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:58:08 by bduval            #+#    #+#             */
/*   Updated: 2025/06/11 18:14:19 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int is_within_cap(t_obj *caps, t_ray *ray, float dist)
{
	if (v_magnitude(v_substract(v_add(ray->start, v_scale(ray->direction, dist)),
					caps->pos)) <= caps->radius)
		return (1);
	return (0);
}

float	caps_collision(t_obj *caps, t_ray *ray)
{
	float	dist;

	dist = plane_colision_dist(caps, ray);
	if (!is_within_cap(caps, ray, dist))
		dist = -1;
	return (dist);
}

