/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:31:55 by bduval            #+#    #+#             */
/*   Updated: 2025/06/28 17:09:06 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	ray->normal = ray->impact_object->normal_fn(ray);
	ray->bump = v_unit(v_substract(
				ray->direction,
				v_scale(ray->normal, 2 * v_dot(ray->direction, ray->normal))));
	ray->from_cam = 0;
	return (0);
}

int	spotlight(t_light *light, t_ray *ray, t_vector view_dir)
{
	t_color		norm_light;
	float		fact_diffuse;
	t_vector	reflection_dir;
	float		spec_angle;

	norm_light = c_scale(c_normalize(light->color), light->brightness);
	fact_diffuse = fmaxf(v_dot(ray->direction, ray->normal), 0);
	ray->direct_light = c_add(ray->direct_light, c_scale(norm_light,
				fact_diffuse));
	if (BONUS)
	{
		reflection_dir = v_unit(v_substract(v_scale(ray->normal, 2 * v_dot(
							ray->direction, ray->normal)), ray->direction));
		spec_angle = fmaxf(v_dot(v_unit(v_neg(view_dir)), reflection_dir), 0);
		ray->specular_light = c_add(ray->specular_light,
				c_scale(norm_light, powf(spec_angle, REFRACT)));
	}
	return (0);
}

int	starting_lights(t_light *amb_light, t_ray *ray)
{
	if (!amb_light)
		return (0);
	ray->direct_light = c_scale(
			c_normalize(amb_light->color),
			amb_light->brightness);
	ray->specular_light = c_set(0);
	return (0);
}

int	reach_spotlight(t_scene *scene, t_light *light, t_ray *ray)
{
	t_vector	to_spotlight;

	to_spotlight = v_substract(light->pos, ray->start);
	ray->shortest_impact_dist = v_magnitude(to_spotlight);
	ray->direction = v_unit(to_spotlight);
	if (v_dot(ray->direction, ray->normal) >= 0 && !get_impact(scene, ray))
		return (1);
	return (0);
}

int	compute_light(t_scene *scene, t_ray *ray)
{
	t_light		*light;
	t_color		surface_color;
	t_vector	view_dir;

	starting_lights(scene->amb_light, ray);
	light = scene->light;
	view_dir = ray->direction;
	set_ray_to_impact(ray);
	while (light && light->type == LIGHT)
	{
		if (reach_spotlight(scene, light, ray))
			spotlight(light, ray, view_dir);
		light = light->next;
	}
	surface_color = ray->impact_object->color_fn(ray->impact_object,
			&ray->normal);
	ray->color = c_multiply(surface_color, ray->direct_light);
	if (BONUS)
		ray->color = c_add(ray->color,
				c_multiply(ray->impact_object->color, ray->specular_light));
	return (0);
}
