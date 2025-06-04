/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:26:57 by rarangur          #+#    #+#             */
/*   Updated: 2025/05/30 13:34:34 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Rotation around the Y axis, looking left or right
void	rotate_yaw(t_vector *v, float angle_radians)
{
	float	x;
	float	z;
	float	cos_;
	float	sin_;

	x = v->x;
	z = v->z;
	cos_ = cos(angle_radians);
	sin_ = sin(angle_radians);
	v->x = x * cos_ - z * sin_;
	v->z = x * sin_ + z * cos_;
}

// Rodrigues rotation formula (see Wikipedia)
//   - cross is the cross vector multiplication (v x axis)
//   - dot is the dot vector multiplication (v . axis)
void	rodrigues(t_vector *v, t_vector *axis, float angle_radian)
{
	float		cos_;
	float		sin_;
	t_vector	cross;
	float		dot;

	cos_ = cos(angle_radian);
	sin_ = sin(angle_radian);
	cross.x = v->y * axis->z - v->z * axis->y;
	cross.y = v->z * axis->x - v->x * axis->z;
	cross.z = v->x * axis->y - v->y * axis->x;
	dot = axis->x * v->x + axis->y * v->y + axis->z * v->z;
	v->x = v->x * cos_ + cross.x * sin_ + axis->x * dot * (1.0 - cos_);
	v->y = v->y * cos_ + cross.y * sin_ + axis->y * dot * (1.0 - cos_);
	v->z = v->z * cos_ + cross.z * sin_ + axis->z * dot * (1.0 - cos_);
}

static t_vector	tangent(t_vector *v)
{
	float		xz_magn;
	t_vector	axis;

	xz_magn = sqrt(v->x * v->x + v->z * v->z);
	if (xz_magn < 1e-10)
	{
		axis.x = 1.0;
		axis.y = 0.0;
		axis.z = 0.0;
	}
	else
	{
		axis.x = v->z / xz_magn;
		axis.y = 0.0;
		axis.z = -v->x / xz_magn;
		if (axis.x < 0)
		{
			axis.x = -axis.x;
			axis.z = -axis.z;
		}
		normalize(&axis);
	}
	return (axis);
}

// Rotation up or down
// If not vertical, uses the tangent in plane XZ as axis for the rotation
// If after rotating it is vertical, adds small degree to not lose the direction
//   - xy_magn is the magnitude of the vector when proyected in plane XZ
//   - axis is the vector tangent to the proyection of v in the plane XZ
void	rotate_pitch(t_vector *v, float angle_radians)
{
	float		xz_magn;
	t_vector	axis;

	axis = tangent(v);
	rodrigues(v, &axis, angle_radians);
	xz_magn = sqrt(v->x * v->x + v->z * v->z);
	if (xz_magn < 1e-6)
		rodrigues(v, &axis, 0.01 * M_PI / 180.0);
}

int	rotate(t_vector *v, float horizontal_angle, float vertical_angle)
{
	if (!horizontal_angle && !vertical_angle)
		return (1);
	if (horizontal_angle)
		rotate_yaw(v, horizontal_angle * M_PI / 180);
	if (vertical_angle)
		rotate_pitch(v, vertical_angle * M_PI / 180);
	return (0);
}
