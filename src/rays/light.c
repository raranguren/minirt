/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:31:55 by bduval            #+#    #+#             */
/*   Updated: 2025/06/03 14:42:44 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define REFRACT	300

int	set_ray_to_light(t_scene *scene, t_ray *ray)
{
	ray->start = v_add(
		ray->start,
		v_scale(ray->direction, ray->shortest_impact_dist));
	ray->normal = ray->impact_object->normal_fn(ray->impact_object, ray->start);
	ray->bump = v_substract(
		ray->direction,
		v_scale(ray->normal, 2 * v_dot(ray->direction, ray->normal)));
	ray->direction = v_unit(v_substract(scene->light->pos, ray->start));
	return (0);
}

int	light(t_scene *scene, t_ray *ray)
{
	if (get_impact(scene, ray))
		return (0);
	ray->direct_light = fmax(v_dot(ray->normal, ray->direction), 0);
	ray->specular_light = fmax(pow(v_dot(ray->bump, ray->direction), REFRACT), 0);
	return (0);
}

int	get_color(t_scene *scene, t_ray *ray)
{
	int		i;
	float	c;

	i = 0;
	while (i < 4)
	{
		c = ray->impact_object->color.argb >> i * 8 & 0xFF;
		c *= ray->direct_light;
		c += ray->specular_light * (scene->light->color.argb << i * 8 & 0xFF);
		c = round(fmin(c, 255));
		ray->color.argb &= ~(0xFF << i * 8);
		ray->color.argb |= (unsigned char)c << i * 8;
		i++;
	}
	return (0);
}

int	compute_light(t_scene *scene, t_ray *ray)
{
	set_ray_to_light(scene, ray);
	light(scene, ray);
	get_color(scene, ray);
	return (0);
}
