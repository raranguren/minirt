/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:51:12 by bduval            #+#    #+#             */
/*   Updated: 2025/06/17 19:35:43 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	static t_all	all;

	if (BONUS)
		ft_putendl_fd(BONUS_WELCOME_MESSAGE, 1);
	else
		ft_putendl_fd(WELCOME_MESSAGE, 1);
	if (ac != 2)
	{
		printf("%s\n", ERROR_ARGUMENTS);
		return (0);
	}
	if (parse_map(ac, av, &all))
		return (free_everything(&all), 1);
	if (set_mlx(&all))
		return (free_everything(&all), 1);
	if (BONUS && init_scene_bonus(&all))
		return (free_everything(&all), 1);
	if (edit_init(&all))
		return (free_everything(&all), 1);
	gui_update(&all);
	send_rays(&all);
	start_mlx_loop(&all);
	save_scene(&all, "snapshot.rt");
	free_everything(&all);
	return (0);
}
