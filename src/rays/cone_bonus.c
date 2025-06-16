/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:34:06 by bduval            #+#    #+#             */
/*   Updated: 2025/06/16 19:58:38 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * w = P - A;
 * k = dot(w, v);
 * m = w - k * v;
 * n = normalize(m * h - v * r)
 * */
t_vector	side_cone_normal(t_obj *cone, t_ray *ray)
{
	t_vector	w;
	t_vector	radial_proj;
	float		axial_proj;
	float		theta;

	w = v_substract(ray->start, cone->pos);
	axial_proj = v_dot(w, cone->orientation);
	radial_proj = v_substract(w, v_scale(cone->orientation, axial_proj));
	theta = atanf(cone->radius / cone->height);
	return (v_unit(v_substract(
					v_scale(v_unit(radial_proj), cosf(theta)),
		 			v_scale(cone->orientation, sinf(theta)))));
}

t_vector	cone_normal(t_ray *ray)
{
	t_vector	cp;
	t_vector	normal;
	float		dist_on_axis;
	t_obj		*cone;

	cone = ray->impact_object;
	cp = v_substract(ray->start, cone->pos);
	dist_on_axis = v_dot(cp, cone->orientation);
	if (dist_on_axis < cone->height - 1e-4)
		normal = side_cone_normal(cone, ray);
	else
		normal = cone->orientation;
	if (v_dot(ray->direction, normal) > 0)
		normal = v_scale(normal, -1.0);
	return (normal);
}

static int	check_caps(t_quadratic *quad, t_obj *cone, t_ray *ray)
{
	float	dist[2];
	t_obj	caps;

	caps.pos = v_add(cone->pos, v_scale(cone->orientation, cone->height));
	caps.radius = cone->radius;
	caps.orientation = cone->orientation;
	dist[0] = caps_collision(&caps, ray);
	if (cone->double_cone)
	{
		caps.pos = v_substract(
				cone->pos, v_scale(cone->orientation, cone->height));
		dist[1] = caps_collision(&caps, ray);
	}
	else
		dist[1] = -1;
	if (!get_positiv_min(&dist[0], &dist[1]))
		return (0);
	if (dist[0] < quad->solution_1)
		quad->solution_1 = dist[0];
	return (1);
}

/*
 * a:			apex cone
 * o:			orient cone (apex to base)
 * h:			height cone (scalar of o)
 * θ:			demi-angle cone (at apex point)
 * r:			radius base
 * rs:			raystart
 * ro:			ray direction
 * w = rs - a	vector from apex to raystart
 *
 * Cone equation for an arbitary p point at its surface:
 *	-> ((p.a).v)² = |p-a|².cos²θ
 * Ray equation
 * 	-> R(t) = rs+t*ro
 *
 * a = ro·o
 * b = w·o
 * k = cos θ			// handy shorthand
 *
 * A = a² − k² |ro|²
 * B = 2( a·b − k² (ro·w) )
 * C = b² − k² |w|²
 * */

static int	set_quadratic(t_quadratic *quad, t_obj *cone, t_ray *ray)
{
	float		teta;
	float		a;
	float		b;
	float		k;
	t_vector	w;

	teta = atanf(cone->radius / cone->height);
	a = v_dot(ray->direction, cone->orientation);
	b = v_dot(v_substract(ray->start, cone->pos), cone->orientation);
	k = cosf(teta);
	w = v_substract(ray->start, cone->pos);
	quad->a = a * a - k * k * v_dot(ray->direction, ray->direction);
	quad->b = 2 * (a * b - k * k * v_dot(ray->direction, w));
	quad->c = b * b - k * k * v_dot(w, w);
	return (0);
}

int	cone_collision(t_obj *cone, t_ray *ray)
{
	t_quadratic quad;
	float		dist_on_axis;

	set_quadratic(&quad, cone, ray);
	if (!solve_quadratic(&quad))
		return (0);
	dist_on_axis = v_dot(v_substract(
				v_add(ray->start, v_scale(ray->direction, quad.solution_1)), cone->pos), cone->orientation);
	if (check_caps(&quad, cone, ray)
			|| (dist_on_axis >= 0 && dist_on_axis < cone->height))
		return (bind_ray_if_nearest(&quad, ray, cone));
	return (0);
}
