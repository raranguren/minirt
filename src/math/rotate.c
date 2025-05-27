/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:26:57 by rarangur          #+#    #+#             */
/*   Updated: 2025/05/27 22:04:36 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rotate(t_vector *v, double horizontal_angle, double vertical_angle)
{
	double	radian_h;
	double	radian_v;
	double	tmp_z;

	radian_h = horizontal_angle * M_PI / 180.0;
	radian_v = vertical_angle * M_PI / 180.0;
	tmp_z = v->x * sin(radian_h) + v->z * cos(radian_h);
	v->x = v->x * cos(radian_h) - v->z * sin(radian_h);
	v->y = v->y * cos(radian_v) - tmp_z * sin(radian_v);
	v->z = v->y * sin(radian_v) + tmp_z * cos(radian_v);
	return (0);
}
