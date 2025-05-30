/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:51:12 by bduval            #+#    #+#             */
/*   Updated: 2025/05/30 09:04:03 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_scene(t_all *all)
{
	t_obj	*ptr;

	printf("CAMERA\n"
		"position	%lf,%lf,%lf\n"
		"orientation	%lf,%lf,%lf\n"
		"fov		%lf\n\n",
		all->scene.cam->pos.x,
		all->scene.cam->pos.y,
		all->scene.cam->pos.z,
		all->scene.cam->orientation.x,
		all->scene.cam->orientation.y,
		all->scene.cam->orientation.z,
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
}

int	main(int ac, char **av)
{
	static t_all	all;

	if (parse_map(ac, av, &all))
		return (free_everything(&all), 1);
	print_scene(&all);
	if (set_mlx(&all))
		return (free_everything(&all), 1);
	free_everything(&all);
	return (0);
}
