/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:29:20 by bduval            #+#    #+#             */
/*   Updated: 2025/06/18 15:13:20 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	get_bump_vector(t_bump *bump, float x, float y)
{
	t_vector	r;
	//char	*pix;

	r.x=0;
	printf("gbv starts : w(%d) h(%d) p(%f, %f)\n", bump->width, bump->height, x, y);
//	pix = bump->map.data + 
//		((int)y * bump->map.line_length + (int)x * (bump->map.bits_per_pix / 8));
//	printf("pix : %d,", *pix++);
//	printf("%d,", *pix++);
//	printf("%d,", *pix++);
//	printf("%d\n", *pix++);
	return (r);
}	
