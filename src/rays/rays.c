/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:08:03 by bduval            #+#    #+#             */
/*   Updated: 2025/06/01 15:24:45 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_the_fundamentals(t_ray *ray, t_cam *cam)
{
	ft_memset(ray, 0, sizeof (t_ray));
	ray->start = cam->pos;
	cam->up.y = 1;
	cam->forward = v_unit(cam->forward);
	cam->right = v_unit(v_cross(cam->up, cam->forward));
	cam->up = v_cross(cam->forward, cam->right);
	cam->aspect_ratio = (double)WIN_WIDTH / WIN_HEIGHT;
	cam->fov_scale = tan(cam->fov * 0.5 * M_PI / 180);
	return (0);
}

int	set_ray(t_ray *ray, t_cam *cam, int x, int y)
{
	t_vector	projection;

	projection.x = (2.0 * (x + 0.5) / WIN_WIDTH - 1);
	projection.x *= cam->aspect_ratio * cam->fov_scale;
	projection.y = 1 - 2.0 * (y + 0.5) / WIN_HEIGHT;
	projection.y *= cam->fov_scale;
	projection.z = 0;
	ray->direction = v_unit(v_add(
				cam->forward,
				v_add(v_scale(cam->right, projection.x),
					v_scale(cam->up, projection.y))));
	ray->color.argb = COLOR_BG;
	ray->shortest_impact_dist = DBL_MAX;
	return (0);
}

int	set_pixel_to_ray_color(t_all *all, t_ray *ray, int x, int y)
{
	mlx_pixel_put(all->mlx_ptr, all->mlx_win, x, y, ray->color.argb);
	return (0);
}

int	get_first_impact(t_scene *scene, t_ray *ray)
{
	int	impact;

	impact = 0;
	scene->selected = scene->obj;
	while (scene->selected)
	{
		impact |= scene->selected->collision_fn(scene->selected, ray);
		scene->selected = scene->selected->next;
	}
	return (impact);
}

int	compute_reflection(t_scene *scene, t_ray *ray)
{
	t_point		point;
	t_vector	normal;
	t_vector	to_light;
	double		dot_product;

	point = v_add(ray->start, v_scale(ray->direction,
				ray->shortest_impact_dist));
	print_vector("point", point);
	normal = ray->impact_object->normal_fn(ray->impact_object, point);
	print_vector("normal", normal);
	to_light = v_unit(v_substract(scene->light->pos, point));
	print_vector("to_light", to_light);
	dot_product = fmax(v_dot(to_light, normal), 0);
	printf("dot -> %lf\n", dot_product);
	ray->color = c_scale(ray->color, dot_product);
	return (0);
}

int	send_rays(t_all *all)
{
	t_ray	ray;
	int		x;
	int		y;

	if (set_the_fundamentals(&ray, all->scene.cam))
		return (-1);
	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			set_ray(&ray, all->scene.cam, x, y);
			if (get_first_impact(&all->scene, &ray))
				compute_reflection(&all->scene, &ray);
			set_pixel_to_ray_color(all, &ray, x, y);
			y++;
		}
		x++;
	}
	return (0);
}
