/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:31:55 by bduval            #+#    #+#             */
/*   Updated: 2025/06/14 22:38:49 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define REFRACT	30

// Set the ray start to the impacted object
// Compute the normal of the surface
// comopute the bump direction of the ray
// init direct_light & specular_light to 1
//int	add_color_to(t_ray *ray, t_color c)
//{
//	
//	return (0);
//}

int	set_ray_to_impact(t_ray *ray)
{
	ray->start = v_add(
			ray->start,
			v_scale(ray->direction, ray->shortest_impact_dist));
	ray->normal = ray->impact_object->normal_fn(ray->impact_object, ray);
	ray->bump = v_unit(v_substract(
				ray->direction,
				v_scale(ray->normal, 2 * v_dot(ray->direction, ray->normal))));
	ray->from_cam = 0;
	return (0);
}

int	spotlight(t_light *light, t_ray *ray)
{
	static t_color	norm_light;
	static float	fact_refract;
	static t_ray	*prev_ray;

	if (!prev_ray || prev_ray != ray)
	{
		norm_light = c_scale(c_normalize(light->color), light->brightness);
		fact_refract = fmax(v_dot(ray->direction, ray->normal), 0);
	}
	ray->direct_light = c_add(ray->direct_light, c_scale(norm_light, fact_refract));
	ray->specular_light = c_add(ray->specular_light,
			c_scale(norm_light, pow(fact_refract, REFRACT)));
	prev_ray = ray;
	return (0);
}

int	starting_lights(t_light *light, t_ray *ray)
{
	ray->direct_light = c_scale(c_normalize(light->color), light->brightness);
	ray->specular_light = c_set(0);
	return (0);
}

int	reach_spotlight(t_scene *scene, t_light *light, t_ray *ray)
{
	t_vector	to_spotlight;

	to_spotlight = v_substract(light->pos, ray->start);
	ray->shortest_impact_dist = v_magnitude(to_spotlight);
	ray->direction = v_unit(to_spotlight);
	if (v_dot(ray->normal, ray->bump) >= 0
		|| v_dot(ray->normal,
			v_unit(v_substract(light->pos, ray->start))) < 0)
		if (!get_impact(scene, ray))
			return (1);
	return (0);
}

int	compute_light(t_scene *scene, t_ray *ray)
{
	t_light	*light;

	starting_lights(scene->amb_light, ray);
	light = scene->light;
	if (set_ray_to_impact(ray))
		light = NULL;
	while (light && light->type == LIGHT)
	{
		if (reach_spotlight(scene, light, ray))
			spotlight(light, ray);
		light = light->next;
	}
	ray->color = c_multiply(ray->impact_object->color, ray->direct_light);
	return (0);
}
