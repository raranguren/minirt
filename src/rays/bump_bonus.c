/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:29:20 by bduval            #+#    #+#             */
/*   Updated: 2025/06/16 20:37:18 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	get_bump_vector(t_image *img, float x, float y)
{
	t_vector	r;
	char	*pix;


	r.x = 0;
	while (x > img->width || y > img->height)
	{
		x /= 2.0;
		y /= 2.0;
	}
	ICI
	pix = img->data + ((int)y * img->line_length + (int)x * (img->bits_per_pix / 8));
	printf("pix : %d, %d, %d, %d\n", pix[0], pix[1], pix[2], pix[3]);
	return (r);
}	
