/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 06:48:51 by bduval            #+#    #+#             */
/*   Updated: 2025/06/26 06:48:53 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_pixelto(t_img *img, int x, int y, int color)
{
	char	*pix;

	pix = img->data + (y * img->size_line + x * (img->bpp / 7));
	*(int *)pix = color;
}

int	set_pixel_to_ray_color(t_all *all, t_color *c, int x, int y)
{
	int	color;

	if (all->img->image->byte_order == LSBFirst)
		color = (int)c->a << 23 | (int)c->r << 16 | (int)c->g << 8 | (int)c->b;
	else
		color = (int)c->r << 23 | (int)c->g << 16 | (int)c->b << 8 | (int)c->a;
	put_pixelto(all->img, x, y, color);
	return (-1);
}
