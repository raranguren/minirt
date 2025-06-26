/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:45:17 by bduval            #+#    #+#             */
/*   Updated: 2025/06/26 23:13:16 by rarangur         ###   ########.fr       */
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

static int	split_and_turntable(char *line, t_scene *scene)
{
	char	**split;
	int		err;

	split = NULL;
	if (split_set(&split, line, SPLIT))
		err = error("Parsing error: split_set()");
	else
		err = turntable(split, scene);
	if (split)
		free_strs(split);
	return (err);
}

static int	read_and_orient(char *path, t_all *all)
{
	int		fd;
	char	*line;
	int		err;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error3("Can't open the file: '", path, "'"));
	line = (char *)1;
	err = 0;
	while (line && !err)
	{
		line = get_next_line(fd);
		if (line && *line)
			err = split_and_turntable(line, &all->scene);
		free(line);
	}
	close(fd);
	return (err);
}

static int	validate_scene(t_scene *scene)
{
	t_obj	*obj;
	int		found_camera;
	int		found_amb;

	if (!scene->obj)
		return (error("The scene has no shapes"));
	found_camera = 0;
	found_amb = 0;
	obj = scene->obj2;
	while (obj)
	{
		if (obj->type == CAMERA)
			found_camera = 1;
		if (obj->type == AMB_LIGHT)
			found_amb = 1;
		obj = obj->next;
	}
	if (!found_camera)
		return (error3("No camera", "\n", CAM_WAITED_VALUES));
	if (!found_amb)
		return (error3("No ambient light", "\n", AMB_LIGHT_WAITED_VALUES));
	return (0);
}

int	parse_map(int ac, char **av, t_all *all)
{
	(void)ac;
	if (ft_strlen(av[1]) < 3
		|| ft_strncmp(&av[1][ft_strlen(av[1]) - 3], ".rt", 3))
		return (error("File path does not end in .rt"));
	if (read_and_orient(av[1], all))
		return (1);
	if (validate_scene(&all->scene))
		return (1);
	if (init_scene(all))
		return (1);
	if (BONUS)
		all->title = ft_strjoin("miniRT_bonus ", av[1]);
	else
		all->title = ft_strjoin("miniRT ", av[1]);
	if (!all->title)
		all->title = "";
	return (0);
}
