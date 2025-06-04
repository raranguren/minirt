/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:14:22 by bduval            #+#    #+#             */
/*   Updated: 2025/06/04 17:07:27 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	sphere_normal(t_obj *obj, t_ray *ray)
{
	t_vector	normal;
	t_point		p;

	p = ray->start;
	normal = v_unit(v_substract(p, obj->pos));
	return (normal);
}

static int	interpret(t_quadratic *res, t_ray *ray, t_obj *obj)
{
	float	dist;

	if (res->solution_1 < 0 && res->solution_2 < 0)
		return (0);
	if (res->solution_1 < 0)
		res->solution_1 = FLT_MAX;
	else if (res->solution_2 < 0)
		res->solution_2 = FLT_MAX;
	dist = fminf(res->solution_1, res->solution_2);
	if (dist < ray->shortest_impact_dist)
	{
		if (ray->from_cam)
		{
			ray->shortest_impact_dist = dist;
			ray->impact_object = obj;
		}
		return (1);
	}
	return (0);
}

int	sphere_collision(t_obj *sphere, t_ray *ray)
{
	t_quadratic	quad;
	t_vector	tmp;

	sphere->radius = (float)sphere->diameter / 2.0;
	tmp = v_substract(ray->start, sphere->pos);
	quad.a = 1.0;
	quad.b = 2.0 * v_dot(tmp, ray->direction);
	quad.c = v_dot(tmp, tmp) - sphere->radius * sphere->radius;
	quad.delta = quad.b * quad.b - 4.0 * quad.a * quad.c;
	if (quad.delta < 0)
		return (0);
	if (quad.delta)
		quad.delta = sqrt(quad.delta);
	quad.solution_1 = (-quad.b - quad.delta) / 2.0;
	quad.solution_2 = (-quad.b + quad.delta) / 2.0;
	return (interpret(&quad, ray, sphere));
}
