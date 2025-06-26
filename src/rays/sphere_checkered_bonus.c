/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_checkered_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:41:46 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/26 21:45:46 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// remap normal vector (assumed normalized) to a 1x1 grid
static void	sphere_to_grid(t_point *grid, t_vector *normal)
{
	float	horizontal_angle;
	float	vertical_angle;

	horizontal_angle = atan2f(normal->z, normal->x);
	vertical_angle = asinf(normal->y);
	grid->x = horizontal_angle / (2.0f * M_PI) + 0.5f;
	grid->y = (vertical_angle + (M_PI / 2.0)) / M_PI;
}

t_color	sphere_checkered(t_obj *obj, t_vector *normal)
{
	t_point	grid;
	int		disruption;

	sphere_to_grid(&grid, normal);
	disruption = ((int)(grid.x * 8) + ((int)(grid.y * 8))) % 2;
	if (disruption)
		return (c_scale(obj->color, 0.2));
	return (obj->color);
}
