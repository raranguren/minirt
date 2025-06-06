/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:54:48 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/06 11:18:33 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*typestr(t_obj *obj)
{
	if (obj->type == CAMERA)
		return ("Camera");
	if (obj->type == AMB_LIGHT)
		return ("Amb. light");
	if (obj->type == LIGHT)
		return ("Light");
	if (obj->type == SPHERE)
		return ("Sphere");
	if (obj->type == PLANE)
		return ("Plane");
	if (obj->type == CYLINDER)
		return ("Cylinder");
	return ("Object");
}

void	tui_update(t_all *all)
{
	t_obj	*obj;

	obj = all->scene.selected;
	printf("%10s ", typestr(obj));
	if (obj->type != CAMERA)
		printf("[%1.2f, %1.2f, %1.2f] ", obj->color.r, obj->color.g,
			obj->color.b);
	else
		printf("           ");
	if (obj->type != AMB_LIGHT)
		printf("📍(% 6.2f, % 6.2f, % 6.2f) ",
			obj->pos.x, obj->pos.y, obj->pos.z);
	if (obj->type == CAMERA || obj->type == PLANE || obj->type == CYLINDER)
		printf("🧭(% 4.2f, % 4.2f, % 4.2f) ",
			obj->orientation.x, obj->orientation.y, obj->orientation.z);
	if (obj->type == SPHERE || obj->type == CYLINDER)
		printf("📏(%6.2f) ", obj->diameter);
	if (obj->type == AMB_LIGHT)
		printf("💡(%3.2f) ", obj->ratio);
	if (obj->type == LIGHT)
		printf("💡(%3.2f) ", obj->brightness);
	if (obj->type == CAMERA)
		printf("📏(%5.1f) ", obj->fov);
	printf("\n");
}

int	ui_update(t_all *all)
{
	tui_update(all);
	return (gui_update(all));
}
