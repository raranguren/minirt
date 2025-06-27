/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:45:06 by bduval            #+#    #+#             */
/*   Updated: 2025/06/27 19:20:45 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	usage(char *a, char *b, char *c)
{
	error3(a, b, c);
	ft_putendl_fd(PLANE_WAITED_VALUES, 2);
	if (BONUS)
		ft_putendl_fd(BONUS_WAITED_VALUES, 2);
	return (1);
}

static int	valid_plane_line(char **param)
{
	int		i;

	i = 1;
	while (param[i])
	{
		if ((i <= 6 && !ft_is_double(param[i]))
			|| (i > 6 && !ft_is_char(param[i])))
		{
			if (i != 10 || !BONUS)
				return (usage("Parse error : invalid '", param[i], "'"));
		}
		i++;
	}
	if (i != 10 && !(BONUS && i == 11))
		return (usage("Parse error: Wrong number of parameters", 0, 0));
	return (0);
}

static int	valid_values(t_obj *plane)
{
	if (!is_normalized(plane->orientation.x)
		|| !is_normalized(plane->orientation.y)
		|| !is_normalized(plane->orientation.z))
		return (usage("Invalid orientation", 0, 0));
	return (0);
}

int	parse_plane(char **param, t_scene *scene)
{
	t_obj	*plane;

	if (valid_plane_line(param))
		return (1);
	plane = ft_calloc(1, sizeof(t_obj));
	if (!plane)
		return (error("Out of memory"));
	plane->type = PLANE;
	if (ft_atoi_double(&plane->pos.x, param[1])
		|| ft_atoi_double(&plane->pos.y, param[2])
		|| ft_atoi_double(&plane->pos.z, param[3])
		|| ft_atoi_double(&plane->orientation.x, param[4])
		|| ft_atoi_double(&plane->orientation.y, param[5])
		|| ft_atoi_double(&plane->orientation.z, param[6]))
		return (usage("Parse error : invalid number", 0, 0));
	if (ft_get_color(plane, &param[7]))
		return (usage("Parse error: invalid color '", param[7], "'"));
	if (BONUS && ft_get_map_name(&plane->bump_name, param[10]))
		return (usage("Parse error: invalid texture name '", param[10], "'"));
	if (valid_values(plane))
		return (1);
	ft_objadd_back(&scene->obj, plane);
	return (0);
}
