/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:24:08 by bduval            #+#    #+#             */
/*   Updated: 2025/05/31 14:10:31 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	loop_hook(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (send_rays(all))
		quit_hook(all);
	return (0);
}

int	start_mlx_loop(t_all *all)
{
	mlx_loop_hook(all->mlx_ptr, &loop_hook, all);
	mlx_loop(all->mlx_ptr);
	return (0);
}
