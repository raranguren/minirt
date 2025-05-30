/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:08:03 by bduval            #+#    #+#             */
/*   Updated: 2025/05/30 12:40:22 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_the_fundamentals(t_ray *ray, t_point *projection, t_cam *cam)
{
	(void)cam;
	ft_memset(projection, 0, sizeof (t_point));
	ft_memset(ray, 0, sizeof (t_ray));
	ray->start = cam->pos;
	return (0);
}

int	update_ray_properties(t_ray *ray, t_cam *cam, t_point *projection)
{
	t_vector	projection_scale;
	t_vector	local_current_proj;
	//t_vector	center_proj;

	projection_scale.x = 2 * tan(cam->fov * M_PI / 180.0);
	projection_scale.y = projection_scale.x * ((double)WIN_HEIGHT / WIN_WIDTH);
	projection_scale.z = 1;
	local_current_proj.x = (projection->x - WIN_WIDTH / 2) / WIN_WIDTH / 2;
	local_current_proj.y = (projection->y - WIN_HEIGHT / 2) / WIN_HEIGHT /2;
	local_current_proj.z = 0;
	local_current_proj = v_cross(local_current_proj, projection_scale);
	ray->direction = v_add(cam->orientation, local_current_proj);
	ray->direction = v_scale(ray->direction, 1 / v_norm(ray->direction));
	ray->color.argb = 0x00ffffff;
	ray->shortest_impact_dist = DBL_MAX;
	return (0);
}

int	set_pixel_to_ray_color(t_all *all, t_ray *ray, t_point *projection)
{
	double	x;
	double	y;

	x = projection->x;
	y = projection->y;
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
	t_point	projection;

	if  (set_the_fundamentals(&ray, &projection, all->scene.cam))
		return (-1);
	while (projection.x < WIN_WIDTH)
	{
		projection.y = 0;
		while (projection.y < WIN_HEIGHT)
		{
			update_ray_properties(&ray, all->scene.cam, &projection);
			all->scene.selected = all->scene.obj;
			while (all->scene.selected)
			{
				all->scene.selected->collision_fn(all->scene.selected, &ray);
				all->scene.selected = all->scene.selected->next;
			}
			set_pixel_to_ray_color(all, &ray, &projection);
			projection.y++;
		}
		projection.x++;
	}
	return (0);
}
