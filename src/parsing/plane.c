/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:45:06 by bduval            #+#    #+#             */
/*   Updated: 2025/05/26 21:04:35 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	valid_plan_line(char **param)
{
	int		i;

	i = 1;
	while (param[i])
	{
		if ((i <= 6 && !ft_is_double(param[i]))
			|| (i > 6 && !ft_is_char(param[i])))
			return (error3("Parse error : invalid '", param[i], "'"));
		i++;
	}
	if (i != 10)
		return (error3("Parse error: Wrong number of parameters", 0, 0));
	return (0);
}

static int	valid_values(t_obj *plane)
{
	if (!is_normalized(plane->orientation.x)
		|| !is_normalized(plane->orientation.y)
		|| !is_normalized(plane->orientation.z))
		return (error3(PLANE_WAITED_VALUES, 0, 0));
	return (0);
}

int	parse_plane(char **param, t_scene *scene)
{
	t_obj	*plane;

	if (valid_plan_line(param))
		return (1);
	plane = ft_calloc(1, sizeof(t_obj));
	plane->type = PLANE;
	if (ft_atoi_double(&plane->pos.x, param[1])
		|| ft_atoi_double(&plane->pos.y, param[2])
		|| ft_atoi_double(&plane->pos.z, param[3])
		|| ft_atoi_double(&plane->orientation.x, param[4])
		|| ft_atoi_double(&plane->orientation.y, param[5])
		|| ft_atoi_double(&plane->orientation.z, param[6]))
		return (error3("Parse error : invalid number", 0, 0));
	if (ft_get_color(&(plane->color), &param[7]))
		return (error3("Parse error: invalid color '", param[7], "'"));
	if (valid_values(plane))
		return (1);
	ft_objadd_back(&scene->obj, plane);
	return (0);
}
