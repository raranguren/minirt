/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bump_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:08:52 by bduval            #+#    #+#             */
/*   Updated: 2025/06/23 11:52:06 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	plane_bump(t_ray *ray)
{
	t_point		p_loc;
	t_vector	modifyer;

	ray->normal = plane_normal(ray);
	p_loc = get_local_cordinates(ray->start, ray->impact_object->orientation,
			ray->impact_object->pos);
	p_loc.x = fabs(p_loc.x);
	p_loc.y = fabs(p_loc.y);
	modifyer = get_bump_vector(ray->impact_object->bump, p_loc);
	ray->normal = add_in_tbn(ray->normal, modifyer);
	return (ray->normal);
}
