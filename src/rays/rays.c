/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:08:03 by bduval            #+#    #+#             */
/*   Updated: 2025/05/30 23:32:40 by bduval           ###   ########.fr       */
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
	cam->fov_scale = ;
	return (0);
}

int	set_ray(t_ray *ray, t_cam *cam,  int x, int y)
{
	t_vector	projection;

	projection.x = (2.0 * (x + 0.5) / WIN_WIDTH - 1);
	projection.x *= cam->aspect_ratio * cam->fov_scale;
	projection.y = 1 - 2.0 * (y + 0.5) / WIN_HEIGHT;
	projection.y *= cam->fov_scale;
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

int	print_ray(t_ray r)
{
	printf("RAY---\npos: %lf,%lf,%lf\ndir: %lf,%lf,%lf\ncol :%i,%i,%i,%i\n\n",
		r.start.x, r.start.y,r.start.z, r.direction.x, r.direction.y, r.direction.z,
		r.color.a, r.color.r, r.color.g, r.color.b);
	return (0);
}

int	send_rays(t_all *all)
{
	t_ray	ray;
	int		x;
	int		y;

	if  (set_the_fundamentals(&ray, all->scene.cam))
		return (-1);
	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			set_ray(&ray, all->scene.cam, x, y);
			all->scene.selected = all->scene.obj;
			while (all->scene.selected)
			{
				all->scene.selected->collision_fn(all->scene.selected, &ray);
				all->scene.selected = all->scene.selected->next;
			}
			set_pixel_to_ray_color(all, &ray, x, y);
			y++;
		}
		x++;
	}
	return (0);
}
