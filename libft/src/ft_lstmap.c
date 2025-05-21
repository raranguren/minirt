/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:16:19 by bduval            #+#    #+#             */
/*   Updated: 2025/05/21 14:09:04 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstnewf(void *content, void *(*f)(void *))
{
	t_list	*l;

	l = ft_lstnew(content);
	if (l)
		l->content = f(l->content);
	return (l);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*current;

	start = NULL;
	while (lst)
	{
		current = ft_lstnewf(lst->content, f);
		if (!current)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		ft_lstadd_back(&start, current);
		lst = lst->next;
	}
	return (start);
}
