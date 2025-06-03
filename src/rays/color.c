/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:23:25 by bduval            #+#    #+#             */
/*   Updated: 2025/06/03 21:59:10 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	c_set(t_color *c, float set)
{
	c->a = set;
	c->r = set;
	c->g = set;
	c->b = set;
	return (0);
}

int	c_scale_c(t_color *c, t_color *scale)
{
	c->a = c->a * scale->a;
	c->r = c->r * scale->r;
	c->g = c->g * scale->g;
	c->b = c->b * scale->b;
	return (0);
}
int	c_scale(t_color *c, float scale)
{
	c->a = c->a * scale;
	c->r = c->r * scale;
	c->g = c->g * scale;
	c->b = c->b * scale;
	return (0);
}
