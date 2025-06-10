/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:01:57 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/10 09:34:46 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	layout_index(char type)
{
	if (type == CAMERA)
		return (0);
	if (type == AMB_LIGHT)
		return (1);
	if (type == LIGHT)
		return (2);
	if (type == PLANE)
		return (3);
	if (type == SPHERE)
		return (4);
	if (type == CYLINDER)
		return (5);
	if (type == CONE)
		return (6);
	return (-1);
}

static char	*background_image(char type)
{
	if (type == CAMERA)
		return (CAMERA_BG);
	if (type == AMB_LIGHT)
		return (AMB_LIGHT_BG);
	if (type == LIGHT)
		return (LIGHT_BG);
	if (type == PLANE)
		return (PLANE_BG);
	if (type == SPHERE)
		return (SPHERE_BG);
	if (type == CYLINDER)
		return (CYLINDER_BG);
	if (type == CONE)
		return (CONE_BG);
	return (NULL);
}

static int	set_layout(t_all *all, char type)
{
	char	*filename;
	int		i;
	int		_;

	i = layout_index(type);
	filename = background_image(type);
	if (!filename || i < 0)
		return (error("UI layout is misconfigured in [gui.c]"));
	if (!all->ui_bg[i])
		all->ui_bg[i] = mlx_xpm_file_to_image(all->mlx_ptr, filename, &_, &_);
	if (!all->ui_bg[i])
		return (error3("Unable to load background image '", filename, "'"));
	mlx_put_image_to_window(all->mlx_ptr, all->mlx_win, all->ui_bg[i],
		WIN_WIDTH, 0);
	return (0);
}

int	gui_update(t_all *all)
{
	static char	type;
	t_obj		*obj;
	int			err;

	err = 0;
	obj = all->scene.selected;
	if (obj->type != type)
		err = set_layout(all, obj->type);
	err |= gui_numbers(all, obj);
	err |= gui_labels(all, obj);
	return (err);
}
