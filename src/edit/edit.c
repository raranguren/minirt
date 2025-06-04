/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:59:43 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/04 15:33:33 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define STEP 10
#define ANGLE 10
#define SIZE 2

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

int	edit_transform(t_all *all, float change, char is_height)
{
	t_obj	*obj;
	float	*value;

	obj = all->scene.selected;
	if (!obj)
		return (1);
	if (is_height && obj->type == SPHERE)
		return (1);
	if (obj->type != SPHERE && obj->type != CYLINDER)
		return (1);
	if (is_height)
		value = &obj->height;
	else
		value = &obj->diameter;
	if (*value + change < 0)
		return (1);
	*value += change;
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

int	edit2(t_all *all, int key)
{
	if (key == XK_v)
		return (edit_transform(all, -SIZE, 0));
	if (key == XK_b)
		return (edit_transform(all, SIZE, 0));
	if (key == XK_x)
		return (edit_transform(all, -SIZE, 1));
	if (key == XK_c)
		return (edit_transform(all, SIZE, 1));
	return (1);
}

int	edit(t_all *all, int key)
{
	if (key == XK_n)
		return (edit_select_next(all));
	if (key == XK_i)
		return (edit_move(all, v_scale(all->scene.cam->forward, STEP)));
	if (key == XK_j)
		return (edit_move(all, v_scale(all->scene.cam->right, -STEP)));
	if (key == XK_k)
		return (edit_move(all, v_scale(all->scene.cam->forward, -STEP)));
	if (key == XK_l)
		return (edit_move(all, v_scale(all->scene.cam->right, STEP)));
	if (key == XK_u)
		return (edit_move(all, v_scale(all->scene.cam->up, STEP)));
	if (key == XK_h)
		return (edit_move(all, v_scale(all->scene.cam->up, -STEP)));
	if (key == XK_Up)
		return (edit_rotate(all, 0, -ANGLE));
	if (key == XK_Down)
		return (edit_rotate(all, 0, ANGLE));
	if (key == XK_Left)
		return (edit_rotate(all, ANGLE, 0));
	if (key == XK_Right)
		return (edit_rotate(all, -ANGLE, 0));
	return (edit2(all, key));
}
