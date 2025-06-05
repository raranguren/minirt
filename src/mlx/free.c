/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:56:50 by bduval            #+#    #+#             */
/*   Updated: 2025/06/05 15:03:13 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	free_mlx(t_all *all)
{
	if (all->img.id)
		mlx_destroy_image(all->mlx_ptr, all->img.id);
	if (all->mlx_win)
		mlx_destroy_window(all->mlx_ptr, all->mlx_win);
	if (all->mlx_ptr)
	{
		mlx_destroy_display(all->mlx_ptr);
		free(all->mlx_ptr);
	}
	return (0);
}
