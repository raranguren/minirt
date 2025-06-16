/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:14:22 by bduval            #+#    #+#             */
/*   Updated: 2025/06/16 09:10:21 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	sphere_normal(t_obj *obj, t_ray *ray)
{
	t_vector	normal;
	t_point		p;

	p = ray->start;
	normal = v_unit(v_substract(p, obj->pos));
	printf("dot : %f\n", v_dot(ray->direction, normal));
	if (v_dot(ray->direction, normal) > 0)
		normal = v_scale(normal, -1.0);
	return (normal);
}

int	sphere_collision(t_obj *sphere, t_ray *ray)
{
	t_quadratic	quad;
	t_vector	tmp;

	tmp = v_substract(ray->start, sphere->pos);
	quad.a = 1.0;
	quad.b = 2.0 * v_dot(tmp, ray->direction);
	quad.c = v_dot(tmp, tmp) - sphere->radius * sphere->radius;
	if (!solve_quadratic(&quad))
		return (0);
	return (bind_ray_if_nearest(&quad, ray, sphere));
}
