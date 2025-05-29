/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:26:57 by rarangur          #+#    #+#             */
/*   Updated: 2025/05/29 21:18:55 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Rotation around the Z axis, looking left or right
void	rotate_yaw(t_vector *v, double angle)
{
	double	radian;

	radian = angle * M_PI / 180.0;
	v->z = v->x * sin(radian) + v->z * cos(radian);
	v->x = v->x * cos(radian) - v->z * sin(radian);
}

// Rodrigues rotation formula (see Wikipedia)
//   - cross is the cross vector multiplication (v x axis)
//   - dot is the dot vector multiplication (v . axis)
void	rodrigues(t_vector *v, t_vector *axis, double angle)
{
	double		cos_a;
	double		sin_a;
	t_vector	cross;
	double		dot;

	cross.x = axis->y * v->z - axis->z * v->y;
	cross.y = axis->z * v->x - axis->x * v->z;
	cross.z = axis->x * v->y - axis->y * v->x;
	dot = axis->x * v->x + axis->y * v->y + axis->z * v->z;
	cos_a = cos(angle);
	sin_a = sin(angle);
	v->x = v->x * cos_a + cross.x * sin_a + axis->x * dot * (1.0 - cos_a);
	v->y = v->y * cos_a + cross.y * sin_a + axis->y * dot * (1.0 - cos_a);
	v->z = v->z * cos_a + cross.z * sin_a + axis->z * dot * (1.0 - cos_a);
}

// Rotation up or down
// If not entirely vertical, uses the tangent in plane XY as axis
// If after rotating it is vertical, adds small degree to not lose the direction
//   - xy_magn is the magnitude of the vector when proyected in plane XY
//   - axis is the vector tangent to the proyection of v in the plane XY
void	rotate_pitch(t_vector *v, double angle)
{
	double		xy_magn;
	t_vector	axis;

	xy_magn = sqrt(v->x * v->x + v->y * v->y);
	if (xy_magn < 1e-10)
	{
		axis.x = 1.0;
		axis.y = 0.0;
		axis.z = 0.0;
	}
	else
	{
		axis.x = -v->y / xy_magn;
		axis.y = v->x / xy_magn;
		axis.z = 0.0;
	}
	rodrigues(v, &axis, angle);
	xy_magn = sqrt(v->x * v->x + v->y * v->y);
	if (xy_magn < 1e-4)
		rodrigues(v, &axis, 0.1);
}

int	rotate(t_vector *v, double horizontal_angle, double vertical_angle)
{
	rotate_yaw(v, horizontal_angle);
	rotate_pitch(v, vertical_angle);
	return (0);
}
