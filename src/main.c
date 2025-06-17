/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:51:12 by bduval            #+#    #+#             */
/*   Updated: 2025/06/17 23:53:57 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	usage(void)
{
	printf("%s\n", ERROR_ARGUMENTS);
	return (0);
}

static void	welcome(void)
{
	if (BONUS)
		ft_putendl_fd(BONUS_WELCOME_MESSAGE, 1);
	else
		ft_putendl_fd(WELCOME_MESSAGE, 1);
}

static int	help(void)
{
	usage();
	write(1, "\n", 1);
	ft_putendl_fd(CAM_WAITED_VALUES, 1);
	write(1, "\n", 1);
	ft_putendl_fd(AMB_LIGHT_WAITED_VALUES, 1);
	write(1, "\n", 1);
	ft_putendl_fd(LIGHT_WAITED_VALUES, 1);
	write(1, "\n", 1);
	ft_putendl_fd(SPHERE_WAITED_VALUES, 1);
	write(1, "\n", 1);
	ft_putendl_fd(PLANE_WAITED_VALUES, 1);
	write(1, "\n", 1);
	ft_putendl_fd(CYLINDER_WAITED_VALUES, 1);
	write(1, "\n", 1);
	ft_putendl_fd(CONE_WAITED_VALUES, 1);
	ft_putendl_fd(BONUS_WAITED_VALUES, 1);
	return (0);
}

int	main(int ac, char **av)
{
	static t_all	all;

	if (ac != 2)
		return (usage());
	welcome();
	if (ft_strcmp("-h", av[1]) == 0 || ft_strcmp("--help", av[1]) == 0)
		return (help());
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
