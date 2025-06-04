/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:52:34 by bduval            #+#    #+#             */
/*   Updated: 2025/06/04 12:26:46 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_mlx(t_all *all)
{
	all->mlx_ptr = mlx_init();
	if (!all->mlx_ptr)
		return (error("mlx_init()"));
	all->mlx_win = mlx_new_window(all->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT, "SCREEN_1");
	if (!all->mlx_win)
		return (error("mlx_new_window()"));
	all->img.id = mlx_new_image(all->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!all->img.id)
		return (error("mlx_new_image()"));
	all->img.data = mlx_get_data_addr(all->img.id, 
		&all->img.bits_per_pix, &all->img.line_length, &all->img.endian);
	if (!all->img.data)
		return (error("mlx_get_data_addr()"));
	set_mlx_events(all);
	send_rays(all);
	start_mlx_loop(all);
	return (0);
}
