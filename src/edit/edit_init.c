/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:54:34 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/16 12:21:46 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	edit_init(t_all *all)
{
	all->scene.selected = all->scene.cam;
	if (all->scene.selected == NULL)
		return (error("[edit_init] no camera"));
	return (0);
}
