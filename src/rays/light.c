/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:31:55 by bduval            #+#    #+#             */
/*   Updated: 2025/06/04 09:41:32 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define REFRACT	30

// Set the ray start to the impacted object
// Compute the normal of the surface
// Return 1 if the ray impact from inside the obj
// comopute the bump direction of the ray
// init direct_light & specular_light to 1
int	set_ray_to_impact(t_ray *ray)
{
	ray->start = v_add(
			ray->start,
			v_scale(ray->direction, ray->shortest_impact_dist));
	ray->normal = ray->impact_object->normal_fn(ray->impact_object, ray->start);
	ray->bump = v_unit(v_substract(
				ray->direction,
				v_scale(ray->normal, 2 * v_dot(ray->direction, ray->normal))));
	ray->direct_light = c_set(1);
	ray->specular_light = c_set(1);
	return (0);
}

int	spotlight(t_light *light, t_ray *ray)
{
	ray->direct_light = c_scale(
			c_multiply(
				ray->direct_light,
				c_scale(c_normalize(light->color), light->brightness)),
			fmax(v_dot(ray->normal, ray->direction), 0));
	ray->specular_light = c_scale(
			c_multiply(
				ray->specular_light,
				c_scale(c_normalize(light->color), light->brightness)),
			pow(fmax(v_dot(ray->normal, ray->direction), 0), REFRACT));
	ray->color = c_multiply(ray->impact_object->color, ray->direct_light);
	ray->color = c_add(
			ray->color, 
			c_multiply(light->color, ray->specular_light));
	return (0);
}

int	amblight(t_light *light, t_ray *ray)
{
	ray->color = c_add(
			ray->color,
			c_multiply(
				ray->impact_object->color,
				c_scale(
					c_normalize(light->color),
					light->brightness))
			);
	return (0);
}

int	compute_light(t_scene *scene, t_ray *ray)
{
	t_light	*light;

	light = scene->light;
	if (set_ray_to_impact(ray))
		light = NULL;
	while (light && light->type == LIGHT)
	{
		ray->direction = v_unit(v_substract(light->pos, ray->start));
		if (!get_impact(scene, ray))
			spotlight(light, ray);
		light = light->next;
	}
	amblight(scene->amb_light, ray);
	return (0);
}
