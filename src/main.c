/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:51:12 by bduval            #+#    #+#             */
/*   Updated: 2025/06/06 14:17:48 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	static t_all	all;

	if (parse_map(ac, av, &all))
		return (free_everything(&all), 1);
	if (set_mlx(&all))
		return (free_everything(&all), 1);
	if (edit_init(&all))
		return (free_everything(&all), 1);
	ui_update(&all);
	send_rays(&all);
	start_mlx_loop(&all);
	free_everything(&all);
	return (0);
}
