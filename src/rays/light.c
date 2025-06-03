/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:31:55 by bduval            #+#    #+#             */
/*   Updated: 2025/06/03 20:36:04 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define REFRACT	30

// Set the ray start to the impacted object
// Compute the normal of the surface
// Return 1 if the ray impact from inside of obj
// comopute the bump direction of the ray
// init direct_light & specular_light to 1
int	set_ray_to_impact(t_ray *ray)
{
	ray->start = v_add(
		ray->start,
		v_scale(ray->direction, ray->shortest_impact_dist));
	ray->normal = ray->impact_object->normal_fn(ray->impact_object, ray->start);
	if (v_dot(ray->direction, ray->normal) < 0)
		return (1);
	ray->bump = v_unit(v_substract(
		ray->direction,
		v_scale(ray->normal, 2 * v_dot(ray->direction, ray->normal))));
	ray->direct_light = 1;
	ray->specular_light = 1;
	return (0);
}

int	get_light_incidence(t_scene *scene, t_ray *ray)
{
	if (get_impact(scene, ray))
		return (0);
	ray->direct_light *= v_dot(ray->normal, ray->direction);
	ray->specular_light *= pow(v_dot(ray->bump, ray->direction), REFRACT);
	return (0);
}

int	compute_final_color(t_light *amb_light, t_ray *ray)
{
	(void)ray;
	(void)amb_light;
	return (0);
}

int	compute_light(t_scene *scene, t_ray *ray)
{
	t_light	*light;

	light = scene->light;
	if (!set_ray_to_impact(ray))
		light = NULL;
	while (light && light->type == LIGHT)
	{
		ray->direction = v_unit(v_substract(light->pos, ray->start));
		get_light_incidence(scene, ray);
		light = light->next;
	}
	compute_final_color(scene->amb_light, ray);
	return (0);
}
