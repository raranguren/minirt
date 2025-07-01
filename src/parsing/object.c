/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:29:29 by bduval            #+#    #+#             */
/*   Updated: 2025/07/01 13:38:55 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_objadd_back(t_obj **lst, t_obj *new)
{
	t_obj	*idx;

	if (*lst == NULL)
	{
		*lst = new;
		return (0);
	}
	idx = *lst;
	while (idx->next)
		idx = idx->next;
	idx->next = new;
	return (0);
}

int	ft_objclear(t_obj **lst, t_all *all)
{
	t_obj	*temp;

	if (!lst || !*lst)
		return (0);
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		if (temp->bump)
			mlx_destroy_image(all->mlx_ptr, temp->bump);
		if (temp->bump_name)
			free(temp->bump_name);
		free(temp);
	}
	*lst = NULL;
	return (0);
}
