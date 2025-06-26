/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_labels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:35:58 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/26 07:23:57 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	gui_label_checkers(t_all *all, t_obj *obj)
{
	(void)obj;
	mlx_string_put(all->mlx_ptr, all->mlx_win,
		WIN_WIDTH + MARGIN_LEFT + COL_WIDTH,
		MARGIN_TOP,
		TEXT_COLOR,
		"+ color disruption");
	return (0);
}

int	gui_label_bumpmap(t_all *all, t_obj *obj)
{
	(void)obj;
	mlx_string_put(all->mlx_ptr, all->mlx_win,
		WIN_WIDTH + MARGIN_LEFT + COL_WIDTH,
		MARGIN_TOP,
		TEXT_COLOR,
		"+ bump map");
	return (0);
}

int	gui_label_color_light_spot(t_all *all, t_obj *obj)
{
	(void)obj;
	mlx_string_put(all->mlx_ptr, all->mlx_win,
		WIN_WIDTH + MARGIN_LEFT + COL_WIDTH,
		MARGIN_TOP,
		TEXT_COLOR,
		"= color spot");
	return (0);
}

static int	is_boring(t_color color)
{
	if (color.r - color.g > 1 || color.r - color.g < -1)
		return (0);
	if (color.r - color.b > 1 || color.r - color.b < -1)
		return (0);
	return (1);
}

int	gui_labels(t_all *all, t_obj *obj)
{
	if (obj->type == LIGHT && !is_boring(obj->color))
		return (gui_label_color_light_spot(all, obj));
	if (!obj->bump_name)
		return (0);
	if (!obj->bump)
		return (gui_label_checkers(all, obj));
	else
		return (gui_label_bumpmap(all, obj));
}
