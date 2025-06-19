/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:56:14 by bduval            #+#    #+#             */
/*   Updated: 2025/06/18 14:42:30 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	proj_on_axis(t_obj *obj, t_point p)
{
	float 		dist;
	
	// p -> cp
	p = v_substract(p, obj->pos);
	dist = v_dot(p, obj->orientation);
	return (dist);
}

t_vector	cylinder_normal(t_ray *ray)
{
	t_vector	normal;
	t_vector	cp;
	float		dist;
	t_obj		*cyl;

	cyl = ray->impact_object;
	cp = v_substract(ray->start, cyl->pos);
	dist = proj_on_axis(cyl, ray->start);
	if (fabs(dist) < cyl->height / 2.0 - EPSLN)
		normal = v_unit(v_substract(cp, v_scale(cyl->orientation, dist)));
	else
	{
		normal = v_unit(v_scale(cyl->orientation, dist));
	}
	if (v_dot(ray->direction, normal) > 0)
		normal = v_scale(normal, -1.0);
	return (normal);
}

static int	set_quadratic(t_quadratic *quad, t_obj *cyl, t_ray *ray)
{
	t_vector	r_c;
	t_vector	r_dir_p;
	t_vector	r_c_p;
	float		rayon;

	//d_|_
	r_dir_p = v_substract(
			ray->direction,
			v_scale(cyl->orientation, v_dot(ray->direction, cyl->orientation)));
	//oc
	r_c = v_substract(ray->start, cyl->pos);
	//oc_|_
	r_c_p = v_substract(r_c,
			v_scale(cyl->orientation, v_dot(r_c, cyl->orientation)));
	rayon = (float)cyl->radius;
	quad->a = v_dot(r_dir_p, r_dir_p);
	quad->b = 2 * v_dot(r_dir_p, r_c_p);
	quad->c = v_dot(r_c_p, r_c_p) - rayon * rayon;
	return (0);
}

static int	cylinder_caps_collision(t_quadratic  *quad, t_obj *cyl, t_ray *ray)
{
	t_obj	caps;
	float	dist[2];

	caps.radius = cyl->radius;
	caps.pos = v_substract(cyl->pos, v_scale(cyl->orientation, cyl->height / 2.0));
	caps.orientation = cyl->orientation;
	dist[0] = caps_collision(&caps, ray);
	caps.pos = v_add(cyl->pos, v_scale(cyl->orientation, cyl->height / 2.0));
	dist[1] = caps_collision(&caps, ray);
	if (!get_positiv_min(&dist[0], &dist[1]))
		return (0);
	if (fabs(proj_on_axis(
		cyl, v_add(ray->start, v_scale(ray->direction, quad->solution_1))))
		> cyl->height / 2.0 || dist[0] < quad->solution_1)
		quad->solution_1 = dist[0];
	return (1);
}

/*  -----	CHECK P is on the real cylinder surface
 *	CP 	= P - C;
 *	CP// = (CP.v).v 
 *		-> dist from C to corresponding P point on v axis
 *		(at which height of the cylinder P is)
 *	CP _|_ = CP - CP//
 *		-> vector radius (||CP_|_|| = radius -> point is on the cylinder)
 *	----
 * */
int	cylinder_collision(t_obj *cyl, t_ray *ray)
{
	t_quadratic	quad;

	set_quadratic(&quad, cyl, ray);
	solve_quadratic(&quad);
	cylinder_caps_collision(&quad, cyl, ray);
	if (fabs(proj_on_axis(
		cyl, v_add(ray->start, v_scale(ray->direction, quad.solution_1))))
			> cyl->height / 2.0 + EPSLN)
		return (0);
	return (bind_ray_if_nearest(&quad, ray, cyl));

}
