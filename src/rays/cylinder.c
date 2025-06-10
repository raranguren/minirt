/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:56:14 by bduval            #+#    #+#             */
/*   Updated: 2025/06/10 15:06:06 by bduval           ###   ########.fr       */
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

int	caps_collision(t_quadratic  *quad, t_obj *cyl, t_ray *ray)
{
	t_obj	caps;
	float	dist[2];

	caps.radius = (float)cyl->diameter / 2.0;
	caps.pos = v_substract(cyl->pos, v_scale(cyl->orientation, cyl->height / 2.0));
	caps.orientation = cyl->orientation;
	dist[0] = plane_colision_dist(&caps, ray);
	if (!is_within_cap(&caps, ray, dist[0]))
		dist[0] = -1;
	caps.pos = v_add(cyl->pos, v_scale(cyl->orientation, cyl->height / 2.0));
	dist[1] = plane_colision_dist(&caps, ray);
	if (!is_within_cap(&caps, ray, dist[1]))
		dist[1] = -1;
	if (!get_positiv_min(&dist[0], &dist[1]))
		return (0);
	return (get_positiv_min(&quad->solution_1, &dist[0]));
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
	t_point 	p;
	t_vector	p_proj_cyl_axis;

	set_quadratic(&quad, cyl, ray);
	if (!solve_quadratic(&quad))
		return (0);
	// p -> rp
	p = v_add(ray->start, v_scale(ray->direction, quad.solution_1));
	// p -> cp
	p = v_substract(p, cyl->pos);
	p_proj_cyl_axis = v_scale(cyl->orientation, v_dot(p, cyl->orientation));
	if (v_magnitude(p_proj_cyl_axis) > cyl->height / 2.0 + 1e-4f)
		if (!caps_collision(&quad, cyl, ray))
			return (0);
	return (bind_ray_if_nearest(&quad, ray, cyl));

}
