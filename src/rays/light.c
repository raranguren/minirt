/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:31:55 by bduval            #+#    #+#             */
/*   Updated: 2025/06/01 20:17:50 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_ray_to_light(t_scene *scene, t_ray *ray)
{
	ray->normal = ray->impact_object->normal_fn(ray->impact_object, ray->start);
	ray->bump = v_substract(
				ray->direction,
				v_scale(ray->normal, 2 * v_dot(ray->direction, ray->normal)));
	ray->direction = v_unit(v_substract(scene->light->pos, ray->start));
	return (0);
}

int	light(t_scene *scene, t_ray *ray)
{
	double	dot;

	if (get_impact(scene, ray))
	{
		ray->direct_light = 0;
		return (0);
	}
	dot = v_dot(ray->normal, ray->direction);
	ray->color.r *= dot * (double)scene->light->color.r / 255;
	ray->color.g *= dot * (double)scene->light->color.g / 255;
	ray->color.b *= dot * (double)scene->light->color.b / 255;
	return (0);
}

int	compute_light(t_scene *scene, t_ray *ray)
{
	set_ray_to_light(scene, ray);
	light(scene, ray);
	specular(scene, ray);
	ambiant(scene, ray);
	retutn (0);
}
