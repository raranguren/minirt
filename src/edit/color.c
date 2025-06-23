/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:02:25 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/23 12:55:55 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	set_color(t_all *all, int r, int g, int b)
{
	t_obj	*obj;

	obj = all->scene.selected;
	if (obj->type == CAMERA)
		return (-1);
	obj->color.r = r;
	obj->color.g = g;
	obj->color.b = b;
	gui_update(all);
	return (0);
}

int	edit_color(t_all *all, int key)
{
	if (key == XK_0)
		return (set_color(all, 40, 40, 40));
	else if (key == XK_1)
		return (set_color(all, 115, 38, 56));
	else if (key == XK_2)
		return (set_color(all, 194, 107, 66));
	else if (key == XK_3)
		return (set_color(all, 255, 204, 0));
	else if (key == XK_4)
		return (set_color(all, 102, 179, 66));
	else if (key == XK_5)
		return (set_color(all, 102, 204, 255));
	else if (key == XK_6)
		return (set_color(all, 66, 115, 255));
	else if (key == XK_7)
		return (set_color(all, 140, 85, 204));
	else if (key == XK_8)
		return (set_color(all, 255, 130, 160));
	else if (key == XK_9)
		return (set_color(all, 255, 255, 255));
	else
		return (-1);
}
