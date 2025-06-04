/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:59:43 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/04 13:12:26 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define	STEP	10

int	edit_rotate(t_all *all, float horizontal, float vertical)
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

int	edit_move(t_all *all, t_vector v)
{
	t_obj	*obj;

	obj = all->scene.selected;
	if (!obj || obj->type == AMB_LIGHT)
		return (1);
	obj->pos.x += v.x;
	obj->pos.y += v.y;
	obj->pos.z += v.z;
	ui_update(all);
	return (0);
}

int	edit_next(t_all *all)
{
	char	type;

	type = all->scene.selected->type;
	all->scene.selected = all->scene.selected->next;
	if (!all->scene.selected)
	{
		if (type & SHAPE)
			all->scene.selected = all->scene.obj2;
		else
			all->scene.selected = all->scene.obj;
	}
	if (all->scene.selected == NULL)
		return (1);
	ui_update(all);
	return (2);
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
	if (key == XK_i)
		return (edit_move(all, v_scale(all->scene.cam->up, STEP)));
	if (key == XK_j)
		return (edit_move(all, v_scale(all->scene.cam->right, -STEP)));
	if (key == XK_k)
		return (edit_move(all, v_scale(all->scene.cam->up, -STEP)));
	if (key == XK_l)
		return (edit_move(all, v_scale(all->scene.cam->right, STEP)));
	if (key == XK_u)
		return (edit_move(all, v_scale(all->scene.cam->forward, STEP)));
	if (key == XK_h)
		return (edit_move(all, v_scale(all->scene.cam->forward, -STEP)));
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
