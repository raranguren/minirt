/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:13:18 by rarangur          #+#    #+#             */
/*   Updated: 2025/05/27 22:04:13 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	normalize(t_vector *v)
{
	float	size;

	if (v->x == 0.0 && v->y == 0.0 && v->z == 0)
		return (1);
	size = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= size;
	v->y /= size;
	v->z /= size;
	return (0);
}
