/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:57:47 by bduval            #+#    #+#             */
/*   Updated: 2025/06/19 15:50:46 by bduval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	usage(char *a, char *b, char *c)
{
	error3(a, b, c);
	ft_putendl_fd(CYLINDER_WAITED_VALUES, 2);
	if (BONUS)
		ft_putendl_fd(BONUS_WAITED_VALUES, 2);
	return (1);
}

static int	valid_cylinder_line(char **param)
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

static int	valid_values(t_obj *cylinder)
{
	if (!is_normalized(cylinder->orientation.x)
		|| !is_normalized(cylinder->orientation.y)
		|| !is_normalized(cylinder->orientation.z)
		|| cylinder->radius < 0
		|| cylinder->height < 0)
		return (usage(CYLINDER_WAITED_VALUES, 0, 0));
	if (normalize(&cylinder->orientation))
		return (usage(CYLINDER_WAITED_VALUES, 0, 0));
	return (0);
}

int	parse_cylinder(char **param, t_scene *scene)
{
	t_obj	*cylinder;

	if (valid_cylinder_line(param))
		return (1);
	cylinder = ft_calloc(1, sizeof(t_obj));
	if (!cylinder)
		return (error("Out of memory"));
	cylinder->type = CYLINDER;
	if (ft_atoi_double(&cylinder->pos.x, param[1])
		|| ft_atoi_double(&cylinder->pos.y, param[2])
		|| ft_atoi_double(&cylinder->pos.z, param[3])
		|| ft_atoi_double(&cylinder->orientation.x, param[4])
		|| ft_atoi_double(&cylinder->orientation.y, param[5])
		|| ft_atoi_double(&cylinder->orientation.z, param[6])
		|| ft_atoi_double(&cylinder->radius, param[7])
		|| ft_atoi_double(&cylinder->height, param[8]))
		return (usage("Parse error : invalid number", 0, 0));
	cylinder->radius /= 2.0;
	if (ft_get_color(cylinder, &param[9]))
		return (usage("Parse error: invalid color '", param[9], "'"));
	if (BONUS && ft_get_map_name(&cylinder->bump.map_name, param[12]))
		return (usage("Parse error: invalid texture name '", param[12], "'"));
	if (valid_values(cylinder))
		return (1);
	return (ft_objadd_back(&scene->obj, cylinder));
}
