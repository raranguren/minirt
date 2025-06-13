/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:03:43 by bduval            #+#    #+#             */
/*   Updated: 2025/06/10 22:56:38 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	valid_cam_line(char **param)
{
	int		i;

	i = 1;
	while (param[i])
	{
		if (i <= 7 && !ft_is_double(param[i]))
			return (error3("Parse error : invalid '", param[i], "'"));
		i++;
	}
	if (i != 8)
		return (error3("Parse error: Wrong number of parameters", 0, 0));
	return (0);
}

static int	check_valid_values(t_cam *cam)
{
	if (cam->orientation.x < -1 || cam->orientation.y < -1
		|| cam->orientation.z < -1
		|| cam->orientation.x > 1 || cam->orientation.y > 1
		|| cam->orientation.z > 1
		|| cam->fov > 180 || cam->fov < 0)
		return (error3(CAM_WAITED_VALUES, 0, 0));
	if (normalize(&cam->orientation))
		return (error3(CAM_WAITED_VALUES, 0, 0));
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
		return (1);
	cam->type = CAMERA;
	err = ft_atoi_double(&cam->pos.x, param[1]);
	err |= ft_atoi_double(&cam->pos.y, param[2]);
	err |= ft_atoi_double(&cam->pos.z, param[3]);
	err |= ft_atoi_double(&cam->orientation.x, param[4]);
	err |= ft_atoi_double(&cam->orientation.y, param[5]);
	err |= ft_atoi_double(&cam->orientation.z, param[6]);
	err |= ft_atoi_double(&cam->fov, param[7]);
	if (err)
		return (error3("Parse error: invalid number for camera", 0, 0));
	if (check_valid_values(cam))
		return (1);
	ft_objadd_back(&scene->obj2, cam);
	return (0);
}
