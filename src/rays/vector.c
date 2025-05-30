/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:48:32 by bduval            #+#    #+#             */
/*   Updated: 2025/05/30 12:24:54 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	v_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	v_add(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

double	v_norm(t_vector v1)
{
	return (sqrt(pow(v1.x, 2) + pow(v1.y, 2) + pow(v1.z, 2)));
}

t_vector	v_scale(t_vector v, double scalar)
{
	v.x *= scalar;
	v.y *= scalar;
	v.z *= scalar;
	return (v);
}

t_vector	v_cross(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = (double)v1.x * v2.x;
	result.y = (double)v1.y * v2.y;
	result.z = (double)v1.z * v2.z;
	return (result);
}

t_vector	v_substract(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}
