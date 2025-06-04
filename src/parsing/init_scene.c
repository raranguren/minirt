/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:04:36 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/04 21:04:23 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	no_collision(t_obj *obj, t_ray *ray)
{
	(void)obj;
	(void)ray;
	return (0);
}

t_collision_fn	collision_fn(char type)
{
	if (type == SPHERE)
		return (&sphere_collision);
	if (type == PLANE)
		return (&plane_collision);
	else
		return (&no_collision);
}

// Function to return the normal vector for a given collision point
// Should not be called if there was no collision point
t_normal_fn	normal_fn(char type)
{
	if (type == SPHERE)
		return (&sphere_normal);
	if (type == PLANE)
		return (&plane_normal);
	else
		return (NULL);
}

// Ensures that the scene has pointers to camera and lights
// Also sets the collision functions to the objets
int	init_scene(t_scene *scene)
{
	t_obj	*obj;
	char	type;

	obj = scene->obj;
	while (obj)
	{
		type = obj->type;
		if (type == CAMERA)
			scene->cam = obj;
		else if (type == AMB_LIGHT)
			scene->amb_light = obj;
		obj->collision_fn = collision_fn(obj->type);
		obj->normal_fn = normal_fn(obj->type);
		obj = find_next_obj_in_scene(scene, obj);
		if (obj == scene->obj)
			break ;
	}
	return (0);
}
