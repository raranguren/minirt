/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:56:14 by bduval            #+#    #+#             */
/*   Updated: 2025/06/08 18:12:41 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	cylinder_normal(t_obj *cyl, t_ray *ray)
{
	t_vector	normal;
	t_vector	cp;
	float		dist_on_cyl_axis;

	cp = v_substract(ray->start, cyl->pos);
	dist_on_cyl_axis = v_dot(cp, cyl->orientation);
	if (fabs(dist_on_cyl_axis) <= (float)cyl->height / 2.0)
		normal = v_unit(v_substract(cp, v_scale(cyl->orientation, dist_on_cyl_axis)));
	else
		normal = v_unit(v_scale(cyl->orientation, dist_on_cyl_axis));
	if (v_dot(normal, ray->bump) < 0)
		normal = v_scale(normal, -1);
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
	rayon = (float)cyl->diameter / 2.0;
	quad->a = v_dot(r_dir_p, r_dir_p);
	quad->b = 2 * v_dot(r_dir_p, r_c_p);
	quad->c = v_dot(r_c_p, r_c_p) - rayon * rayon;
	return (0);
}

int is_within_cap(t_obj *caps, t_ray *ray, float dist)
{
	if (v_magnitude(v_substract(v_add(ray->start, v_scale(ray->direction, dist)),
					caps->pos)) <= caps->radius)
		return (1);
	return (0);
}

int	caps_collision(float *ret_dist, t_obj *cyl, t_ray *ray)
{
	t_obj	caps;
	float	dist[2];
	int		r;

	r = 0;
	caps.radius = (float)cyl->diameter / 2.0;
	caps.pos = v_substract(cyl->pos, v_scale(cyl->orientation, cyl->height / 2.0));
	caps.orientation = cyl->orientation;
	dist[0] = plane_colision_dist(&caps, ray);
	if (dist[0] > 0 && !is_within_cap(&caps, ray, dist[0]))
		dist[0] = -1;
	caps.pos = v_substract(cyl->pos, v_scale(cyl->orientation, -cyl->height / 2.0));
	dist[1] = plane_colision_dist(&caps, ray);
	if (dist[1] > 0 && !is_within_cap(&caps, ray, dist[1]))
		dist[1] = -1;
	if (dist[0] > 0 && dist[0] < dist[1] && ++r)
		*ret_dist = dist[0];
	else if (dist[1] > 0 && ++r)
		*ret_dist = dist[1];
	return (r);
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
int	corps_collision(t_quadratic *quad, t_obj *cyl, t_ray *ray)
{
	t_point 	p;
	t_vector	p_proj_cyl_axis;
	float		dist_from_axis;

	if (!solve_quadratic(quad))
		return (0);
	// p -> rp 
	p = v_add(ray->start, v_scale(ray->direction, quad->solution_1));
	// p -> cp
	p = v_substract(p, cyl->pos);
	p_proj_cyl_axis = v_scale(cyl->orientation, v_dot(p, cyl->orientation));
	if (v_magnitude(p_proj_cyl_axis) < (float)cyl->height / 2.0)
		return (0);
	dist_from_axis = v_magnitude(v_substract(p, p_proj_cyl_axis));
	if (dist_from_axis < ((float) cyl->diameter / 2.0))
		return (0);
	return (1);
}

int	caps_or_corp(t_quadratic *quad, t_obj *cyl, t_ray *ray)
{
	float	dist_nearest_caps;
	int		err1;
	int		err2;

	dist_nearest_caps = -1;
	err1 = caps_collision(&dist_nearest_caps, cyl, ray);
	err2 = corps_collision(quad, cyl, ray);
	if (!err1 && !err2)
		return (0);
	if (dist_nearest_caps > 0 && quad->solution_1 > 0
			&& dist_nearest_caps < quad->solution_1)
		quad->solution_1 = dist_nearest_caps;
	return (1);
}

int	cylinder_collision(t_obj *cyl, t_ray *ray)
{
	t_quadratic	quad;
	set_quadratic(&quad, cyl, ray);
	if (!caps_or_corp(&quad, cyl, ray))
		return (0);
	ICI
	return (bind_ray_if_nearest(&quad, ray, cyl));
}
