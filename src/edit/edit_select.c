/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:57:08 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/14 22:27:42 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	edit_select(t_all *all, t_obj *target)
{
	if (target == all->scene.selected)
		return (1);
	all->scene.selected = target;
	gui_update(all);
	return (0);
}

// assumes there is at least a camera in obj2
// but the lists of shapes (obj) and lights can be empty
t_obj	*find_next_obj_in_scene(t_scene *scene, t_obj *this)
{
	if (!this)
		return (scene->obj);
	if (this->next)
		return (this->next);
	if (this->type & SHAPE)
		return (scene->obj2);
	if (this->type == LIGHT)
	{
		if (scene->obj)
			return (scene->obj);
		return (scene->obj2);
	}
	if (scene->light)
		return (scene->light);
	return (scene->obj2);
}

int	edit_select_next(t_all *all)
{
	all->scene.selected = find_next_obj_in_scene(
			&all->scene, all->scene.selected);
	if (all->scene.selected == NULL)
		return (error("[edit_select] Memory error in the list of objects"));
	gui_update(all);
	return (2);
}

int	edit_select_previous(t_all *all)
{
	t_obj	*obj;
	t_obj	*previous;

	previous = all->scene.selected;
	obj = find_next_obj_in_scene(&all->scene, all->scene.selected);
	while (obj != all->scene.selected)
	{
		previous = obj;
		obj = find_next_obj_in_scene(&all->scene, obj);
	}
	all->scene.selected = previous;
	gui_update(all);
	return (2);
}
