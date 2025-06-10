/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:09:22 by bduval            #+#    #+#             */
/*   Updated: 2025/06/10 14:52:19 by bduval           ###   ########.fr       */
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

static int	set_to_max(float *f)
{
	*f = FLT_MAX;
	return (0);
}

int	get_positiv_min(float *f1, float *f2)
{
	float	tmp;
	tmp = fmaxf(*f1, *f2);
	if (tmp < 0)
		return (set_to_max(f1));
	*f1 = fminf(*f1, *f2);
	if (*f1 < 0)
		*f1 = tmp;
	return (1);
}

int	solve_quadratic(t_quadratic *quad)
{
	quad->delta = quad->b * quad->b - 4.0 * quad->a * quad->c;
	if (quad->delta < 0)
		return (set_to_max(&quad->solution_1));
	if (quad->delta)
		quad->delta = sqrt(quad->delta);
	quad->solution_1 = (-quad->b - quad->delta) / 2.0 * quad->a;
	quad->solution_2 = (-quad->b + quad->delta) / 2.0 * quad->a;
	return (get_positiv_min(&quad->solution_1, &quad->solution_2));
}

/*
 *	Solve Quadratic equation,
 *	return 0 if no solution or both solution are < 0
 *	store the lowest positive solution in solution_1
 * */
