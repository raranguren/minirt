/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:29:20 by bduval            #+#    #+#             */
/*   Updated: 2025/06/16 19:52:33 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	get_bump_vector(t_image *img, float u, float v)
{
	t_vector	r;
	(void)u;
	(void)v;
	r.x = 0;
	r.y = 0;
	r.z = 0;
	printf("bpp : %d\n", img->bits_per_pix);
	return (r);
}	
