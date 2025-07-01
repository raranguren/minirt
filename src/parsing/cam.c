/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:03:43 by bduval            #+#    #+#             */
/*   Updated: 2025/07/01 13:20:26 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	usage(char *a, char *b, char *c)
{
	error3(a, b, c);
	ft_putendl_fd(CAM_WAITED_VALUES, 2);
	return (1);
}

static int	valid_cam_line(char **param)
{
	int		i;

	i = 1;
	while (param[i])
	{
		if (i <= 7 && !ft_is_double(param[i]))
			return (usage("Parse error : invalid '", param[i], "'"));
		i++;
	}
	if (i != 8)
		return (usage("Wrong number of parameters", 0, 0));
	return (0);
}

static int	check_valid_values(t_cam *cam)
{
	if (cam->orientation.x < -1 || cam->orientation.y < -1
		|| cam->orientation.z < -1
		|| cam->orientation.x > 1 || cam->orientation.y > 1
		|| cam->orientation.z > 1)
		return (usage("Invalid orientation", 0, 0));
	if (cam->fov > 180 || cam->fov < 0)
		return (usage("Parse error: FOV is not between 0 and 180", 0, 0));
	if (cam->fov == 180)
		cam->fov = 179.99;
	if (normalize(&cam->orientation))
		return (usage("Unable to normalize orientation", 0, 0));
	return (0);
}

int	parse_cam(char **param, t_scene *scene)
{
	t_cam	*cam;
	int		err;

	if (valid_cam_line(param))
		return (1);
	cam = ft_calloc(1, sizeof(t_cam));
	if (!cam)
		return (error("Out of memory"));
	cam->type = CAMERA;
	err = ft_atoi_double(&cam->pos.x, param[1]);
	err |= ft_atoi_double(&cam->pos.y, param[2]);
	err |= ft_atoi_double(&cam->pos.z, param[3]);
	err |= ft_atoi_double(&cam->orientation.x, param[4]);
	err |= ft_atoi_double(&cam->orientation.y, param[5]);
	err |= ft_atoi_double(&cam->orientation.z, param[6]);
	err |= ft_atoi_double(&cam->fov, param[7]);
	if (err)
		return (usage("Parse error: invalid values for camera", 0, 0));
	if (check_valid_values(cam))
		return (1);
	ft_objadd_back(&scene->obj2, cam);
	return (0);
}
