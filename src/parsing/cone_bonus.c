/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:57:47 by bduval            #+#    #+#             */
/*   Updated: 2025/06/07 14:24:09 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
				return (error3("Parse error : invalid '", param[i], "'"));
		}
		i++;
	}
	if (i != 12 && !(BONUS && i == 13))
		return (error3("Parse error: Wrong number of parameters", 0, 0));
	return (0);
}

static int	valid_values(t_obj *cone)
{
	if (!is_normalized(cone->orientation.x)
		|| !is_normalized(cone->orientation.y)
		|| !is_normalized(cone->orientation.z)
		|| cone->diameter < 0
		|| cone->height < 0)
		return (error3(CONE_WAITED_VALUES, 0, 0));
	if (normalize(&cone->orientation))
		return (error3(CONE_WAITED_VALUES, 0, 0));
	return (0);
}

int	parse_cone(char **param, t_scene *scene)
{
	t_obj	*cone;

	if (valid_cone_line(param))
		return (1);
	cone = ft_calloc(1, sizeof(t_obj));
	cone->type = CONE;
	if (ft_atoi_double(&cone->pos.x, param[1])
		|| ft_atoi_double(&cone->pos.y, param[2])
		|| ft_atoi_double(&cone->pos.z, param[3])
		|| ft_atoi_double(&cone->orientation.x, param[4])
		|| ft_atoi_double(&cone->orientation.y, param[5])
		|| ft_atoi_double(&cone->orientation.z, param[6])
		|| ft_atoi_double(&cone->diameter, param[7])
		|| ft_atoi_double(&cone->height, param[8]))
		return (error3("Parse error : invalid number", 0, 0));
	if (ft_get_color(cone, &param[9]))
		return (error3("Parse error: invalid color '", param[9], "'"));
	if (BONUS && ft_get_map_name(&cone->map_name, param[12]))
		return (error3("Parse error: invalid texture name '", param[12], "'"));
	if (valid_values(cone))
		return (1);
	ft_objadd_back(&scene->obj, cone);
	return (0);
}
