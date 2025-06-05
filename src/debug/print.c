/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:04:37 by bduval            #+#    #+#             */
/*   Updated: 2025/06/05 12:36:59 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	print_ray(t_ray r)
{
	printf("RAY---\npos: %lf,%lf,%lf\ndir: %lf,%lf,%lf\ncol :%f,%f,%f,%f\n\n",
		r.start.x, r.start.y, r.start.z, r.direction.x,
		r.direction.y, r.direction.z,
		r.color.a, r.color.r, r.color.g, r.color.b);
	return (0);
}

int	print_color(char *s, t_color c)
{
	printf("%s -> (%f,\t%f,\t%f,\t%f)\n", s, c.a, c.r, c.g, c.b);
	return (0);
}

int	print_vector(char *s, t_vector v)
{
	printf("%s -> (%lf,\t%lf,\t%lf)\n", s, v.x, v.y, v.z);
	return (0);
}
