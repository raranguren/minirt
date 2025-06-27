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
