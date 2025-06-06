/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:45:17 by bduval            #+#    #+#             */
/*   Updated: 2025/06/06 21:54:25 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	turntable(char **line, t_scene *scene)
{
	if (!line || !*line || !ft_strncmp(*line, "\n", 1))
		return (0);
	if (!ft_strcmp(*line, "A"))
		return (unique(AMB_LIGHT, parse_amb_light(line, scene)));
	else if (!ft_strcmp(*line, "C"))
		return (unique(CAMERA, parse_cam(line, scene)));
	else if (!ft_strcmp(*line, "L"))
		return (unique(LIGHT, parse_light(line, scene)));
	else if (!ft_strcmp(*line, "sp"))
		return (parse_sphere(line, scene));
	else if (!ft_strcmp(*line, "pl"))
		return (parse_plane(line, scene));
	else if (!ft_strcmp(*line, "cy"))
		return (parse_cylinder(line, scene));
	else if (BONUS && !ft_strcmp(*line, "co"))
		return (parse_cone(line, scene));
	else
		return (error3("Invalid identifier: ", *line, 0));
	return (0);
}

static int	read_and_orient(char *path, t_all *all)
{
	int		fd;
	char	*line;
	char	**split;
	int		err;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error3("Can't find the file: '", path, "'"));
	line = (char *)1;
	err = 0;
	while (line && !err)
	{
		line = get_next_line(fd);
		if (line && *line)
		{
			split = NULL;
			if (split_set(&split, line, SPLIT))
				return (error3("Parse error: ", strerror(errno), 0));
			err = turntable(split, &all->scene);
			free_strs(split);
		}
		free(line);
	}
	close(fd);
	return (err);
}

int	parse_map(int ac, char **av, t_all *all)
{
	if (ac != 2 || ft_strlen(av[1]) < 3
		|| ft_strncmp(&av[1][ft_strlen(av[1]) - 3], ".rt", 3))
		return (error3(ERROR_ARGUMENTS, 0, 0));
	if (read_and_orient(av[1], all))
		return (-1);
	init_scene(all);
	return (0);
}
