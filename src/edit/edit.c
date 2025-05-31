/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:59:43 by rarangur          #+#    #+#             */
/*   Updated: 2025/05/30 13:33:08 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	edit_rotate(t_all *all, double horizontal, double vertical)
{
	t_obj	*obj;

	obj = all->scene.selected;
	if (!obj)
		return (1);
	if (obj->type != CAMERA && obj->type != CYLINDER && obj->type != PLANE)
		return (1);
	rotate(&obj->orientation, horizontal, vertical);
	ui_update(all);
	return (0);
}

int	edit_move(t_all *all, double x, double y, double z)
{
	t_obj	*obj;

	obj = all->scene.selected;
	if (!obj || obj->type == AMB_LIGHT)
		return (1);
	obj->pos.x += x;
	obj->pos.y += y;
	obj->pos.z += z;
	ui_update(all);
	return (0);
}

int	edit_next(t_all *all)
{
	all->scene.selected = all->scene.selected->next;
	if (!all->scene.selected)
		all->scene.selected = all->scene.obj;
	if (all->scene.selected == NULL)
		return (1);
	ui_update(all);
	return (0);
}

int	edit_init(t_all *all)
{
	all->scene.selected = all->scene.cam;
	if (all->scene.selected == NULL)
		return (1);
	ui_update(all);
	return (0);
}

int	edit(t_all *all, int key)
{
	if (key == XK_n)
		return (edit_next(all));
	if (key == XK_w)
		return (edit_move(all, 0, 10, 0));
	if (key == XK_s)
		return (edit_move(all, 0, -10, 0));
	if (key == XK_a)
		return (edit_move(all, -10, 0, 0));
	if (key == XK_d)
		return (edit_move(all, 10, 0, 0));
	if (key == XK_e)
		return (edit_move(all, 0, 0, 10));
	if (key == XK_c)
		return (edit_move(all, 0, 0, -10));
	if (key == XK_Up)
		return (edit_rotate(all, 0, -10));
	if (key == XK_Down)
		return (edit_rotate(all, 0, 10));
	if (key == XK_Left)
		return (edit_rotate(all, 10, 0));
	if (key == XK_Right)
		return (edit_rotate(all, -10, 0));
	return (1);
}
