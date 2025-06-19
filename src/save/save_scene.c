/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:09:58 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/19 15:52:31 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	save_scene(t_all *all, char *filename)
{
	int		fd;
	t_obj	*old_selected;
	int		count;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (error3("Can't open file '", filename, "' to save the scene"));
	old_selected = all->scene.selected;
	all->scene.selected = all->scene.obj2;
	count = 0;
	while (!count || all->scene.selected != all->scene.obj2)
	{
		put_obj_fd(all->scene.selected, fd);
		count++;
		edit_select_next(all);
	}
	close(fd);
	all->scene.selected = old_selected;
	printf("Scene saved to '%s'\n", filename);
	return (0);
}
