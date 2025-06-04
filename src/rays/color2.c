/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:23:25 by bduval            #+#    #+#             */
/*   Updated: 2025/06/04 17:13:51 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	c_scale(t_color c, float scale)
{
	c.a = c.a * scale;
	c.r = c.r * scale;
	c.g = c.g * scale;
	c.b = c.b * scale;
	return (c_range(c));
}
