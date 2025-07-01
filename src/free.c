/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:44:53 by bduval            #+#    #+#             */
/*   Updated: 2025/07/01 13:39:51 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	free_strs(char **strs)
{
	int	i;

	if (!strs)
		return (0);
	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (0);
}

int	free_scene(t_all *all)
{
	ft_objclear(&all->scene.obj, all);
	ft_objclear(&all->scene.obj2, all);
	ft_objclear(&all->scene.light, all);
	return (0);
}

int	free_everything(t_all *all)
{
	free_mlx(all);
	free_scene(all);
	return (0);
}
