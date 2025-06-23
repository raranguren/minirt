/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:52:34 by bduval            #+#    #+#             */
/*   Updated: 2025/06/23 07:53:22 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_mlx(t_all *all)
{
	all->mlx_ptr = mlx_init();
	if (!all->mlx_ptr)
		return (error("mlx_init()"));
	all->mlx_win = mlx_new_window(all->mlx_ptr, WIN_WIDTH + UI_WIDTH,
			WIN_HEIGHT, "SCREEN_1");
	if (!all->mlx_win)
		return (error("mlx_new_window()"));
	all->img = mlx_new_image(all->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!all->img)
		return (error("mlx_new_image()"));
	set_mlx_events(all);
	mlx_set_font(all->mlx_ptr, all->mlx_win, TEXT_FONT);
	errno = 0;
	return (0);
}
// loop starts in main.c
