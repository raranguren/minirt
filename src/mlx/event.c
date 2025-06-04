/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:59:13 by bduval            #+#    #+#             */
/*   Updated: 2025/06/04 12:25:30 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	quit_hook(void *param)
{
	mlx_loop_end(((t_all *)param)->mlx_ptr);
	return (0);
}

static int	expose_hook(void *param)
{
	(void)param;
	return (0);
}

static int	key_press_hook(int keycode, void *param)
{
	if (keycode == XK_Escape)
		quit_hook(param);
	if (edit(param, keycode) == 0)
	{
		send_rays((t_all*)param);
		return (0);
	}
	// handle other keys, debugging etc.
	return (0);
}

static int	mouse_hook(int button, int x, int y, void *param)
{
	(void)button;
	(void)x;
	(void)y;
	(void)param;
	return (0);
}

int	set_mlx_events(t_all *all)
{
	mlx_mouse_hook(all->mlx_win, &mouse_hook, all);
	mlx_hook(all->mlx_win, KeyPress, KeyPressMask, &key_press_hook, all);
	mlx_hook(all->mlx_win, DestroyNotify, KeyPressMask, &quit_hook, all);
	mlx_expose_hook(all->mlx_win, &expose_hook, all);
	return (0);
}
