/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 21:43:55 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/07 23:58:39 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_color_disruption(t_obj *obj)
{
	if (obj->type == SPHERE)
		obj->color_fn = obj->color_fn;
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
		obj->normal_fn = obj->normal_fn;
	else if (obj->type == PLANE)
		return (error3("Unsupported '", obj->map_name, "' for PLANE"));
	else if (obj->type == CYLINDER)
		return (error3("Unsupported '", obj->map_name, "' for CYLINDER"));
	else if (obj->type == CONE)
		return (error3("Unsupported '", obj->map_name, "' for CONE"));
	img = mlx_xpm_file_to_image(all->mlx_ptr, obj->map_name, &tmp, &tmp);
	if (!img)
		return (error3("Could not load xpm texture from file '",
				obj->map_name, "'"));
	obj->map.id = img;
	mlx_get_data_addr(img, &obj->map.bits_per_pix,
		&obj->map.line_length, &obj->map.endian);
	return (0);
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
		if (obj->map_name)
		{
			if (ft_strcmp(obj->map_name, "#") == 0)
			{
				if (set_color_disruption(obj))
					return (-1);
			}
			else if (set_bump_map(all, obj))
				return (-1);
		}
		obj = find_next_obj_in_scene(scene, obj);
	}
	return (0);
}
