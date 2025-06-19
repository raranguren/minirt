/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:29:29 by bduval            #+#    #+#             */
/*   Updated: 2025/06/18 14:10:46 by bduval           ###   ########.fr       */
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

int	ft_objclear(t_obj **lst)
{
	t_obj	*temp;

	if (!lst || !*lst)
		return (0);
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		if (temp->bump.map.id)
			free(temp->bump.map.id);
		if (temp->bump.map_name)
			free(temp->bump.map_name);
		free(temp);
	}
	*lst = NULL;
	return (0);
}
