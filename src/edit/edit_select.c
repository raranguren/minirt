/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:57:08 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/04 15:50:51 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	edit_select(t_all *all, t_obj *target)
{
	if (target == all->scene.selected)
		return (1);
	all->scene.selected = target;
	ui_update(all);
	return (0);
}

int	edit_select_next(t_all *all)
{
	char	type;

	type = all->scene.selected->type;
	all->scene.selected = all->scene.selected->next;
	if (!all->scene.selected)
	{
		if (type & SHAPE)
			all->scene.selected = all->scene.obj2;
		else
			all->scene.selected = all->scene.obj;
	}
	if (all->scene.selected == NULL)
		return (1);
	ui_update(all);
	return (2);
}
