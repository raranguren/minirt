/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:14:22 by bduval            #+#    #+#             */
/*   Updated: 2025/05/30 21:22:02 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Ray equation  :  R(t)= ray->start + t * ray->orientation;
// Point is at the sphere  surface if ||R(t) - sphere->pos||² = sphere->rayon
// After developpment we get the final equation :
//	t² + 2 * (L . D)t + (L . L - sphere->rayon²) = 0
//	with L = ray->start - sphere->pos
//	so a = 1	b = 2(L . D)	c = L . L - r2
//	Delta = b²-4ac
//	if Delta > 0  	>> 2 results : 
//		-> (-b + sqr_root(delta)) / 2a
//		-> (-b - sqr_root(delta)) / 2a
//	if Delta = 0  	>> 1 results : 
//		-> -b / 2a
//	if Delta < 0	>> 0 results :
//	printf("Ray :\n start %lf, %lf, %lf\n orient : %lf,%lf,%lf\n",
//			ray->start.x,ray->start.y,ray->start.z,ray->direction.x,ray->direction.y,ray->direction.z);
static int	interpret_results(t_quadratic *res, t_ray *ray, t_obj *obj)
{
	if ((res->solution_1 < 0 || res->solution_1 > ray->shortest_impact_dist)
		&& (res->solution_2 < 0 || res->solution_2 > ray->shortest_impact_dist))
			return (0);
	if (res->solution_1 < ray->shortest_impact_dist)
		ray->shortest_impact_dist = res->solution_1;
	if (res->solution_2 < ray->shortest_impact_dist)
		ray->shortest_impact_dist = res->solution_2;
	ray->impact_object = obj;
	ray->color.argb = obj->color.argb;
	return (0);
}

int	sphere_collision(t_obj *sphere, t_ray *ray)
{
	t_quadratic	quad;
	t_vector	tmp;

	tmp = v_substract(ray->start, sphere->pos);
	quad.a = 1.0;
	quad.b = 2.0 * v_dot(tmp, ray->direction);
	quad.c = v_dot(tmp, tmp) - (double)sphere->diameter / 2 * (double)sphere->diameter / 2;
	quad.delta = quad.b * quad.b - 4.0 * quad.c;
	if (quad.delta < 0)
		return (0);
	if (quad.delta)
		quad.delta = sqrt(quad.delta);
	quad.solution_1 = (double)(-quad.b - quad.delta ) / 2.0;
	quad.solution_2 = (double)(-quad.b + quad.delta ) / 2.0;
	interpret_results(&quad, ray, sphere);
	return(0);
}
