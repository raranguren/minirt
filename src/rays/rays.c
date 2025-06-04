/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:08:03 by bduval            #+#    #+#             */
/*   Updated: 2025/06/04 12:33:47 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_the_cam(t_cam *cam)
{
	cam->up.y = 1;
	cam->forward = v_unit(cam->forward);
	cam->right = v_unit(v_cross(cam->up, cam->forward));
	cam->up = v_cross(cam->forward, cam->right);
	cam->aspect_ratio = (float)WIN_WIDTH / WIN_HEIGHT;
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
	ray->from_cam = 1;
	return (0);
}

void	put_pixelto(t_image *img, int x, int y, int color)
{
	char	*pix;

	pix = img->data + (y * img->line_length + x * (img->bits_per_pix / 8));
	*(int *)pix = color;
}

int	set_pixel_to_ray_color(t_all *all, t_color *c, int x, int y)
{
	int	color;

	color = (int)c->a << 24 | (int)c->r << 16 | (int)c->g << 8 | (int)c->b;
	put_pixelto(&all->img, x, y, color);
	return (0);
}

int	get_impact(t_scene *scene, t_ray *ray)
{
	int		impact;
	t_obj	*obj;

	impact = 0;
	obj = scene->obj;
	while (obj)
	{
		if (obj != ray->impact_object)
			impact |= obj->collision_fn(obj, ray);
		obj = obj->next;
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
				set_pixel_to_ray_color(all, &ray.color, x, y);
			}
			else
				put_pixelto(&all->img, x, y, COLOR_BG);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(all->mlx_ptr, all->mlx_win, all->img.id, 0, 0);
	return (0);
}
