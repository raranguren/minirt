/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:09:22 by bduval            #+#    #+#             */
/*   Updated: 2025/06/05 17:08:42 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	bind_ray_if_nearest(t_quadratic *res, t_ray *ray, t_obj *obj)
{
	if (res->solution_1 < ray->shortest_impact_dist)
	{
		if (ray->from_cam)
		{
			ray->shortest_impact_dist = res->solution_1;
			ray->impact_object = obj;
		}
		return (1);
	}
	return (0);
}

static int	exit_quad(t_quadratic *quad)
{
	quad->solution_1 = FLT_MAX;
	return (0);
}

int	solve_quadratic(t_quadratic *quad)
{
	float	tmp;

	quad->delta = quad->b * quad->b - 4.0 * quad->a * quad->c;
	if (quad->delta < 0)
		return (exit_quad(quad));
	if (quad->delta)
		quad->delta = sqrt(quad->delta);
	quad->solution_1 = (-quad->b - quad->delta) / 2.0;
	quad->solution_2 = (-quad->b + quad->delta) / 2.0;
	tmp = fmaxf(quad->solution_1, quad->solution_2);
	if (tmp < 0)
		return (exit_quad(quad));
	quad->solution_1 = fminf(quad->solution_1, quad->solution_2);
	quad->solution_2 = tmp;
	if (quad->solution_1 < 0)
		quad->solution_1 = quad->solution_2;
	return (1);
}

/*
 *	Solve Quadratic equation, 
 *	return 0 if no solution or both solution are < 0
 *	store the lowest positive solution in solution_1
 * */
