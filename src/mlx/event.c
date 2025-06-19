/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:59:13 by bduval            #+#    #+#             */
/*   Updated: 2025/06/19 10:10:50 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	key_press_hook(int keycode, void *all)
{
	if (keycode == XK_Escape)
		mlx_loop_end(((t_all *)all)->mlx_ptr);
	if (edit(all, keycode) == 0)
	{
		send_rays(all);
		return (0);
	}
	return (0);
}

static int	mouse_hook(int button, int x, int y, void *all)
{
	if (x > WIN_WIDTH || y > WIN_HEIGHT)
		return (0);
	if (button == Button1)
	{
		mouse_left_click(all, x, y);
		send_rays(all);
	}
	else if (button == Button3)
	{
		mouse_right_click(all, x, y);
		send_rays(all);
	}
	return (0);
}

static int	motion1_hook(int x, int y, t_all *all)
{
	if (x > WIN_WIDTH || y > WIN_HEIGHT)
		return (0);
	if (all->scene.selected->type | SHAPE)
	{
		mouse_left_move(all, x, y);
		gui_update(all);
	}
	return (0);
}

static int	releas_hook(int button, int x, int y, t_all *all)
{
	if (button == Button1 && all->scene.selected->type | SHAPE)
		send_rays(all);
	(void)x;
	(void)y;
	return (0);
}

int	set_mlx_events(t_all *all)
{
	mlx_mouse_hook(all->mlx_win, &mouse_hook, all);
	mlx_key_hook(all->mlx_win, &key_press_hook, all);
	mlx_hook(all->mlx_win, DestroyNotify, None, &mlx_loop_end, all->mlx_ptr);
	mlx_hook(all->mlx_win, MotionNotify, Button1MotionMask, &motion1_hook, all);
	mlx_hook(all->mlx_win, ButtonRelease, ButtonReleaseMask, &releas_hook, all);
	return (0);
}
