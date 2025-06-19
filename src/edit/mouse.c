/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:51:44 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/19 10:15:06 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mouse_left_click(t_all *all, int x, int y)
{
	t_ray	ray;

	init_ray(&ray, all->scene.cam, x, y);
	if (get_impact(&all->scene, &ray))
		edit_select(all, ray.impact_object);
	else
		edit_select(all, all->scene.cam);
}

void	mouse_left_move(t_all *all, int x, int y)
{
	t_ray		ray;
	t_vector	rel_pos;
	float		distance;

	rel_pos = v_substract(all->scene.selected->pos, all->scene.cam->pos);
	distance = v_magnitude(rel_pos);
	init_ray(&ray, all->scene.cam, x, y);
	rel_pos = v_scale(ray.direction, distance);
	all->scene.selected->pos = v_add(all->scene.cam->pos, rel_pos);
}

void	mouse_right_click(t_all *all, int x, int y)
{
	t_ray	ray;

	init_ray(&ray, all->scene.cam, x, y);
	all->scene.cam->orientation = ray.direction;
	gui_update(all);
}
