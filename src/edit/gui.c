/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:01:57 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/06 16:21:29 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	int		tmp;

	filename = background_image(type);
	if (!filename)
		return (0);
	all->ui_bg = mlx_xpm_file_to_image(all->mlx_ptr, filename, &tmp, &tmp);
	if (!all->ui_bg)
		return (error3("Unable to load background image '", filename, "'"));
	return (0);
}

static int	put_obj_info(t_all *all, t_obj *obj)
{
	(void)all;
	(void)obj;
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
		err = set_layout(all, type);
	err |= put_obj_info(all, obj);
	return (err);
}
