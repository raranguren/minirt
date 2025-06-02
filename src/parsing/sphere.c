/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:57:47 by bduval            #+#    #+#             */
/*   Updated: 2025/06/02 09:58:21 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	valid_sphere_line(char **param)
{
	int		i;

	i = 1;
	while (param[i])
	{
		if ((i <= 4 && !ft_is_double(param[i]))
			|| (i > 4 && !ft_is_char(param[i])))
			return (error3("Parse error : invalid '", param[i], "'"));
		i++;
	}
	if (i != 8)
		return (error3("Parse error: Wrong number of parameters", 0, 0));
	return (0);
}

static int	valid_values(t_obj *sphere)
{
	if (sphere->diameter < 0)
		return (error3(SPHERE_WAITED_VALUES, 0, 0));
	return (0);
}

int	parse_sphere(char **param, t_scene *scene)
{
	t_obj	*sphere;

	if (valid_sphere_line(param))
		return (1);
	sphere = ft_calloc(1, sizeof(t_obj));
	if (!sphere)
		return (1);
	sphere->type = SPHERE;
	if (ft_atoi_double(&sphere->pos.x, param[1])
		|| ft_atoi_double(&sphere->pos.y, param[2])
		|| ft_atoi_double(&sphere->pos.z, param[3])
		|| ft_atoi_double(&sphere->diameter, param[4]))
		return (error3("Parse error : invalid number", 0, 0));
	if (ft_get_color(sphere, &param[5]))
		return (error3("Parse error: invalid color '", param[5], "'"));
	if (valid_values(sphere))
		return (1);
	ft_objadd_back(&scene->obj, sphere);
	return (0);
}
