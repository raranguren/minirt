/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:56:50 by bduval            #+#    #+#             */
/*   Updated: 2025/06/23 07:18:44 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_ui(t_all *all)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (all->ui_bg[i])
			mlx_destroy_image(all->mlx_ptr, all->ui_bg[i]);
		i++;
	}
	if (all->ui_color_box)
		mlx_destroy_image(all->mlx_ptr, all->ui_color_box);
}

int	free_mlx(t_all *all)
{
	free_ui(all);
	if (all->img)
		mlx_destroy_image(all->mlx_ptr, all->img);
	if (all->mlx_win)
		mlx_destroy_window(all->mlx_ptr, all->mlx_win);
	if (all->mlx_ptr)
	{
		mlx_destroy_display(all->mlx_ptr);
		free(all->mlx_ptr);
	}
	return (0);
}
