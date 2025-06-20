/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:29:20 by bduval            #+#    #+#             */
/*   Updated: 2025/06/20 10:21:01 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


static char	get_pixel_value(t_img *img, unsigned int x, unsigned int y)
{
	char	*p;

	p = img->data +
		(y * img->size_line + x * (img->bpp / 8));
	
	return (*p);
}
/*
 Return the tangeant and bitangeant of the normal factors
 p :  x, y coordinates [-1:1]
 */
t_vector	get_bump_vector(t_bump *bump, t_point p)
{
	float	height;
	float	height_x;
	float	height_y;
	float	step;

	p.x = p.x * bump->width;
	p.y = p.y * bump->height;
	step = EPSLN * bump->width;
	if (p.x - step < 0)
		height_x = p.x + step;
	else
		height_x = p.x - step;
	step = EPSLN * bump->height;
	if (p.y - step < 0)
		height_y = p.y + step;
	else
		height_y = p.y - step;
	height = get_pixel_value(bump->map.id, p.x, p.y);
	height_x = get_pixel_value(bump->map.id, height_x, p.y);
	height_y = get_pixel_value(bump->map.id, p.x, height_y);
	p.x = ((float)height - height_x) / EPSLN;
	p.y = ((float)height - height_y) / EPSLN;
	p = v_scale(p, BUMP_STRENGTH);
	return (p);
}	
