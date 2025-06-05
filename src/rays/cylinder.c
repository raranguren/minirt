/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:56:14 by bduval            #+#    #+#             */
/*   Updated: 2025/06/05 14:59:25 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	cylinder_normal(t_obj *obj, t_ray *ray)
{
	t_vector	normal;
	normal = ray->direction;
	(void)obj;
	(void)ray;
	return (normal);
}

/* -----	Get len r.dir to impact infinite cylinder 
 * 	P = r.start + r.dir * len
 *
 * -----	CHECK P is on the real cylinder surface
 *	CP 	= P - C;
 *	CP// = (CP.v).v 
 *		-> dist from C to corresponding P point on v axis
 *		(at which height of the cylinder P is)
 *	CP _|_ = CP - CP//
 *		-> vector radius (||CP_|_|| = radius -> point is on the cylinder)
 *	----
 * */
static int	set_quadratic(t_quadratic *quad, t_obj *cyl, t_ray *ray)
{
	t_vector	r_c;
	t_vector	r_dir_p;
	t_vector	r_c_p;

	//d_|_
	r_dir_p = v_substract(
			ray->direction, 
			v_scale(cyl->orientation, v_dot(ray->direction, cyl->orientation)));
	//oc
	r_c = v_substract(cyl->pos, ray->start);
	//oc_|_
	r_c_p = v_substract(r_c, 
			v_scale(cyl->orientation, v_dot(r_c, cyl->orientation)));
	quad->a = v_dot(r_dir_p, r_dir_p);
	quad->b = 2 * v_dot(r_dir_p, r_c_p);
	quad->c = v_dot(r_c_p, r_c_p) - (float)cyl->diameter / 2;
	return (0);
}
int	cylinder_collision(t_obj *cyl, t_ray *ray)
{
	t_quadratic	quad;
	//t_point		p;

	set_quadratic(&quad, cyl, ray);
	if (!solve_quadratic(&quad))
		return (0);
	return (bind_ray_if_nearest(&quad, ray, cyl));
//	p = v_add(ray->start, v_scale(ray->direction, quad.solution_1));
//	if (on_cyl_corp(p, cyl))
	
	return (1);
}
