/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_obj_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:39:30 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/18 14:10:26 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	put3(float a, float b, float c, int fd)
{
	ft_putfloat_fd(a, fd);
	ft_putstr_fd(",", fd);
	ft_putfloat_fd(b, fd);
	ft_putstr_fd(",", fd);
	ft_putfloat_fd(c, fd);
	ft_putstr_fd("\t", fd);
}

static void	put1(float a, int fd)
{
	ft_putfloat_fd(a, fd);
	ft_putstr_fd("\t", fd);
}

static void	put_cylinder_fd(t_obj *obj, int fd)
{
	if (obj->type == CONE)
		ft_putstr_fd("co\t", fd);
	else
		ft_putstr_fd("cy\t", fd);
	put3(obj->pos.x, obj->pos.y, obj->pos.z, fd);
	put3(obj->orientation.x, obj->orientation.y, obj->orientation.z, fd);
	put1(obj->radius * 2, fd);
	put1(obj->height, fd);
}

static void	put_shape_fd(t_obj *obj, int fd)
{
	if (obj->type == SPHERE)
	{
		ft_putstr_fd("sp\t", fd);
		put3(obj->pos.x, obj->pos.y, obj->pos.z, fd);
		put1(obj->radius * 2, fd);
	}
	else if (obj->type == PLANE)
	{
		ft_putstr_fd("pl\t", fd);
		put3(obj->pos.x, obj->pos.y, obj->pos.z, fd);
		put3(obj->orientation.x, obj->orientation.y, obj->orientation.z, fd);
	}
	else if (obj->type == CYLINDER || obj->type == CONE)
		put_cylinder_fd(obj, fd);
}

void	put_obj_fd(t_obj *obj, int fd)
{
	if (obj->type == AMB_LIGHT)
	{
		ft_putstr_fd("A\t", fd);
		put1(obj->brightness, fd);
	}
	else if (obj->type == CAMERA)
	{
		ft_putstr_fd("C\t", fd);
		put3(obj->pos.x, obj->pos.y, obj->pos.z, fd);
		put3(obj->orientation.x, obj->orientation.y, obj->orientation.z, fd);
		put1(obj->fov, fd);
	}
	else if (obj->type == LIGHT)
	{
		ft_putstr_fd("L\t", fd);
		put3(obj->pos.x, obj->pos.y, obj->pos.z, fd);
		put1(obj->brightness, fd);
	}
	else
		put_shape_fd(obj, fd);
	if (obj->type != CAMERA)
		// TODO colors * 255
		put3(obj->color.r * 1, obj->color.g * 1, obj->color.b * 1, fd);
	if (obj->bump.map_name)
		ft_putstr_fd(obj->bump.map_name, fd);
	write(fd, "\n", 1);
}
