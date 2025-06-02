/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:08:03 by bduval            #+#    #+#             */
/*   Updated: 2025/06/02 15:48:29 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_the_cam(t_cam *cam)
{
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

	ft_memset(ray, 0, sizeof (t_ray));
	ray->start = cam->pos;
	projection.x = (2.0 * (x + 0.5) / WIN_WIDTH - 1);
	projection.x *= cam->aspect_ratio * cam->fov_scale;
	projection.y = 1 - 2.0 * (y + 0.5) / WIN_HEIGHT;
	projection.y *= cam->fov_scale;
	projection.z = 0;
	ray->direction = v_unit(v_add(
				cam->forward,
				v_add(v_scale(cam->right, projection.x),
					v_scale(cam->up, projection.y))));
	ray->shortest_impact_dist = DBL_MAX;
	return (0);
}

int	set_pixel_to_ray_color(t_all *all, int	color, int x, int y)
{
	mlx_pixel_put(all->mlx_ptr, all->mlx_win, x, y, color);
	return (0);
}

int	get_impact(t_scene *scene, t_ray *ray)
{
	int	impact;

	impact = 0;
	scene->selected = scene->obj;
	while (scene->selected)
	{
		if (scene->selected != ray->impact_object)
			impact |= scene->selected->collision_fn(scene->selected, ray);
		scene->selected = scene->selected->next;
	}
	return (impact);
}

int	send_rays(t_all *all)
{
	t_ray	ray;
	int		x;
	int		y;

	if (set_the_cam(all->scene.cam))
		return (-1);
	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			set_ray(&ray, all->scene.cam, x, y);
			if (get_impact(&all->scene, &ray))
			{
				compute_light(&all->scene, &ray);
				set_pixel_to_ray_color(all, ray.color.argb, x, y);
			}
			else
				set_pixel_to_ray_color(all, COLOR_BG, x, y);
			y++;
		}
		x++;
	}
	return (0);
}
