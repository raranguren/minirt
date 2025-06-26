/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 21:43:55 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/26 21:12:14 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_color_disruption(t_obj *obj)
{
	if (obj->type == SPHERE)
		obj->color_fn = sphere_checkered;
	else if (obj->type == PLANE)
		return (error3("Unsupported color disruption '#' for PLANE", 0, 0));
	else if (obj->type == CYLINDER)
		return (error3("Unsupported color disruption '#' for CYLINDER", 0, 0));
	else if (obj->type == CONE)
		return (error3("Unsupported color disruption '#' for CONE", 0, 0));
	return (0);
}

int	set_bump_map(t_all *all, t_obj *obj)
{
	t_img	*img;
	int		tmp;

	if (obj->type == SPHERE)
		obj->normal_fn = sphere_bump;
	else if (obj->type == PLANE)
		obj->normal_fn = plane_bump;
	else if (obj->type == CYLINDER)
		obj->normal_fn = cylinder_bump;
	else if (obj->type == CONE)
		obj->normal_fn = cone_bump;
	img = mlx_xpm_file_to_image(all->mlx_ptr, obj->bump_name,
			&tmp, &tmp);
	if (!img)
		return (error3("Could not load xpm texture from file '",
				obj->bump_name, "'"));
	obj->bump = img;
	return (0);
}

int	is_xpm_file(char *filename)
{
	if (ft_strcmp(filename + ft_strlen(filename) - 4, ".xpm") != 0)
		return (!error3("'", filename, "' not a '.xpm' file"));
	return (1);
}

int	init_scene_bonus(t_all *all)
{
	t_scene	*scene;
	t_obj	*obj;

	scene = &all->scene;
	obj = NULL;
	while (obj != scene->obj)
	{
		if (!obj)
			obj = scene->obj;
		if (obj->bump_name)
		{
			if (ft_strcmp(obj->bump_name, "#") == 0)
			{
				if (set_color_disruption(obj))
					return (-1);
			}
			else if (!is_xpm_file(obj->bump_name) || set_bump_map(all, obj))
				return (-1);
		}
		obj = find_next_obj_in_scene(scene, obj);
	}
	return (0);
}
