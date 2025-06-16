/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:57:47 by bduval            #+#    #+#             */
/*   Updated: 2025/06/16 20:31:47 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	usage(char *a, char *b, char *c)
{
	error3(a, b, c);
	ft_putendl_fd(CONE_WAITED_VALUES, 2);
	return (1);
}

static int	valid_cone_line(char **param)
{
	int		i;

	i = 1;
	while (param[i])
	{
		if ((i <= 8 && !ft_is_double(param[i]))
			|| (i > 8 && !ft_is_char(param[i])))
		{
			if (i != 12 || !BONUS)
				return (usage("Parse error : invalid '", param[i], "'"));
		}
		i++;
	}
	if (i != 12 && !(BONUS && i == 13))
		return (usage("Parse error: Wrong number of parameters", 0, 0));
	return (0);
}

static int	valid_values(t_obj *cone)
{
	if (!is_normalized(cone->orientation.x)
		|| !is_normalized(cone->orientation.y)
		|| !is_normalized(cone->orientation.z)
		|| cone->radius < 0
		|| cone->height < 0)
		return (usage(CONE_WAITED_VALUES, 0, 0));
	if (normalize(&cone->orientation))
		return (usage(CONE_WAITED_VALUES, 0, 0));
	return (0);
}

int	parse_cone(char **param, t_scene *scene)
{
	t_obj	*cone;

	if (valid_cone_line(param))
		return (1);
	cone = ft_calloc(1, sizeof(t_obj));
	if (!cone)
		return (error("Out of memory"));
	cone->type = CONE;
	if (ft_atoi_double(&cone->pos.x, param[1])
		|| ft_atoi_double(&cone->pos.y, param[2])
		|| ft_atoi_double(&cone->pos.z, param[3])
		|| ft_atoi_double(&cone->orientation.x, param[4])
		|| ft_atoi_double(&cone->orientation.y, param[5])
		|| ft_atoi_double(&cone->orientation.z, param[6])
		|| ft_atoi_double(&cone->radius, param[7])
		|| ft_atoi_double(&cone->height, param[8]))
		return (usage("Parse error : invalid number", 0, 0));
	cone->radius /= 2.0;
	if (ft_get_color(cone, &param[9]))
		return (usage("Parse error: invalid color '", param[9], "'"));
	if (BONUS && ft_get_map_name(&cone->map_name, param[12]))
		return (usage("Parse error: invalid texture name '", param[12], "'"));
	if (valid_values(cone))
		return (1);
	return (ft_objadd_back(&scene->obj, cone));
}
