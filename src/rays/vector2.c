/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:48:32 by bduval            #+#    #+#             */
/*   Updated: 2025/06/04 09:04:28 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	v_dot(t_vector v1, t_vector v2)
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

t_vector	v_unit(t_vector v)
{
	return (v_scale(v, 1.0 / v_magnitude(v)));
}

float	v_magnitude(t_vector v1)
{
	float	res;

	res = v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
	if (res)
		res = sqrt(res);
	return (res);
}

t_vector	v_scale(t_vector v, float scalar)
{
	v.x *= scalar;
	v.y *= scalar;
	v.z *= scalar;
	return (v);
}
