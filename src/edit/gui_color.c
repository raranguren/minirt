/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 04:02:42 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/19 08:52:19 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	put(t_img *img, int x, int y, t_color c)
{
	char	*pix;

	pix = img->data + y * img->size_line + x * img->bpp / 8;
	*(int *)pix = (int)c.r << 16 | (int)c.g << 8 | (int)c.b;
}

static void	border(t_img *img)
{
	static t_color	black;

	put(img, 0, 0, black);
	put(img, 1, 0, black);
	put(img, 0, 1, black);
	put(img, img->width - 1, img->height - 1, black);
	put(img, img->width - 2, img->height - 1, black);
	put(img, img->width - 1, img->height - 2, black);
	put(img, img->width - 1, 0, black);
	put(img, img->width - 2, 0, black);
	put(img, img->width - 1, 1, black);
	put(img, 0, img->height - 1, black);
	put(img, 1, img->height - 1, black);
	put(img, 0, img->height - 2, black);
}

static void	fill(t_img *img, t_color c)
{
	int	x;
	int	y;

	y = img->height;
	while (y)
	{
		y--;
		x = img->width;
		while (x)
		{
			x--;
			put(img, x, y, c);
		}
	}
}

int	gui_color(t_all *all, t_obj *obj)
{
	static t_img	*img;

	if (!img)
	{
		img = mlx_new_image(all->mlx_ptr, 19, 14);
		if (!img)
			return (error("Image for color box not created"));
		all->ui_color_box = img;
	}
	fill(img, obj->color);
	border(img);
	mlx_put_image_to_window(all->mlx_ptr, all->mlx_win, img,
		WIN_WIDTH + MARGIN_LEFT,
		MARGIN_TOP - 15 + 1);
	return (0);
}
