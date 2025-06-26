/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snap_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:04:26 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/20 23:13:55 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	coords_to_grid(t_coord *pos)
{
	pos->x = round(pos->x / STEP_GRID) * STEP_GRID;
	pos->y = round(pos->y / STEP_GRID) * STEP_GRID;
	pos->z = round(pos->z / STEP_GRID) * STEP_GRID;
}

//static void	round_angles(t_vector *v)
//{
//	double	angle_horizontal;
//	double	angle_elevation;
//	double	hypotenuse_xz;
//
//	normalize(v);
//	angle_horizontal = atan2(v->x, v->z) * 180.0 / M_PI;
//	hypotenuse_xz = sqrt(v->x * v->x + v->z * v->z);
//	angle_horizontal = round(angle_horizontal / STEP_ANGLE) * STEP_ANGLE;
//	angle_elevation = atan2(v->y, hypotenuse_xz) * 180.0 / M_PI;
//	angle_elevation = round(angle_elevation / STEP_ANGLE) * STEP_ANGLE;
//	v->x = sin(angle_horizontal * M_PI / 180.0);
//	v->z = cos(angle_horizontal * M_PI / 180.0);
//	v->y = sin(angle_elevation * M_PI / 180.0);
//}
//
//int	snap_obj(t_obj *obj)
//{
//	if (obj->type == AMB_LIGHT)
//		return (-1);
//	coords_to_grid(&obj->pos);
//	if (obj->type == CAMERA || obj->type == PLANE || obj->type == CYLINDER
//		|| obj->type == CONE)
//		round_angles(&obj->orientation);
//	return (0);
//}
int	snap_obj(t_obj *obj)
{
	if (obj->type == AMB_LIGHT)
		return (-1);
	coords_to_grid(&obj->pos);
	return (0);
}

int	edit_snap(t_all *all)
{
	int	no_change;

	no_change = snap_obj(all->scene.selected);
	if (no_change)
		return (1);
	gui_update(all);
	return (0);
}
