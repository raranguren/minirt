/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:47:11 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/09 19:11:17 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	gui_put_str(t_all *all, int x, int y, char *str)
{
	mlx_string_put(all->mlx_ptr, all->mlx_win,
		WIN_WIDTH + MARGIN_LEFT + x * COL_WIDTH,
		MARGIN_TOP + y * ROW_HEIGHT,
		TEXT_COLOR,
		str);
}

void	gui_put_float(t_all *all, int x, int y, double f)
{
	char	buff[10];
	int		n;
	int		i;

	i = ft_strlcpy(buff, "    0.00", 10);
	if (f < 0)
	{
		buff[0] = '-';
		f = -f;
	}
	n = round(f * 100.0);
	i = 7;
	while (i > 0 && n > 0)
	{
		buff[i] = '0' + n % 10;
		n /= 10;
		i--;
		if (i == 5)
			i--;
	}
	n = f;
	gui_put_str(all, x, y, buff);
}

void	gui_put_color(t_all *all, int x, int y, t_color color)
{
	char	buff[10];
	int		i;

	i = ft_strlcpy(buff, "0xFFFFFF", 10);
	(void)color;
	buff[i] = '\0';
	gui_put_str(all, x, y, buff);
}

int	gui_numbers(t_all *all, t_obj *obj)
{
	if (obj->type == CAMERA)
		gui_put_float(all, 0, 0, obj->fov);
	else
		gui_put_color(all, 0, 0, obj->color);
	if (obj->type != AMB_LIGHT)
	{
		gui_put_float(all, 0, 1, obj->pos.x);
		gui_put_float(all, 1, 1, obj->pos.y);
		gui_put_float(all, 2, 1, obj->pos.z);
	}
	if (obj->type == CYLINDER || obj->type == SPHERE || obj->type == CONE)
		gui_put_float(all, 0, 2, obj->diameter);
	else if (obj->type == LIGHT)
		gui_put_float(all, 0, 2, obj->ratio);
	if (obj->type == CAMERA || obj->type == CYLINDER
		|| obj->type == CONE || obj->type == PLANE)
	{
		gui_put_float(all, 0, 3, obj->orientation.x);
		gui_put_float(all, 1, 3, obj->orientation.y);
		gui_put_float(all, 2, 3, obj->orientation.z);
	}
	if (obj->type == CYLINDER || obj->type == CONE)
		gui_put_float(all, 0, 4, obj->height);
	return (0);
}
