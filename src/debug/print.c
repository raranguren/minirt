/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:04:37 by bduval            #+#    #+#             */
/*   Updated: 2025/05/31 14:23:26 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	print_scene(t_all *all)
{
	t_obj	*ptr;

	printf("CAMERA\n"
		"position	%lf,%lf,%lf\n"
		"orientation	%lf,%lf,%lf\n"
		"fov		%lf\n\n",
		all->scene.cam->pos.x,
		all->scene.cam->pos.y,
		all->scene.cam->pos.z,
		all->scene.cam->forward.x,
		all->scene.cam->forward.y,
		all->scene.cam->forward.z,
		all->scene.cam->fov);
	printf("AMBLIGHT\n"
		"brightness	%lf\n"
		"color		%d,%d,%d\n\n",
		all->scene.amb_light->brightness,
		all->scene.amb_light->color.r,
		all->scene.amb_light->color.g,
		all->scene.amb_light->color.b);
	printf("LIGHT\n"
		"position		%lf,%lf,%lf\n"
		"brightness		%lf\n"
		"color			%d,%d,%d\n\n",
		all->scene.light->pos.x,
		all->scene.light->pos.y,
		all->scene.light->pos.z,
		all->scene.light->brightness,
		all->scene.light->color.r,
		all->scene.light->color.g,
		all->scene.light->color.b);
	ptr = all->scene.obj;
	while (ptr)
	{
		printf("OBJECT\n"
			"type			%#04x\n"
			"position		%lf,%lf,%lf\n"
			"orientation		%lf,%lf,%lf\n"
			"dimensions		%lf,%lf\n"
			"color			%d,%d,%d\n"
			"next			%p\n\n",
			ptr->type,
			ptr->pos.x,
			ptr->pos.y,
			ptr->pos.z,
			ptr->orientation.x,
			ptr->orientation.y,
			ptr->orientation.z,
			ptr->diameter,
			ptr->height,
			ptr->color.r,
			ptr->color.g,
			ptr->color.b,
			ptr->next);
		ptr = ptr->next;
	}
	return (0);
}

int	print_ray(t_ray r)
{
	printf("RAY---\npos: %lf,%lf,%lf\ndir: %lf,%lf,%lf\ncol :%i,%i,%i,%i\n\n",
		r.start.x, r.start.y, r.start.z, r.direction.x,
		r.direction.y, r.direction.z,
		r.color.a, r.color.r, r.color.g, r.color.b);
	return (0);
}

int	print_color(char *s, t_color c)
{
	printf("%s -> (%d,\t%d,\t%d,\t%d)\n", s, c.a, c.r, c.g, c.b);
	return (0);
}

int	print_vector(char *s, t_vector v)
{
	printf("%s -> (%lf,\t%lf,\t%lf)\n", s, v.x, v.y, v.z);
	return (0);
}
