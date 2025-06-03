/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 07:49:56 by bduval            #+#    #+#             */
/*   Updated: 2025/06/02 22:28:09 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	valid_light_line(char **param)
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

static int	valid_values(t_light *light)
{
	if (light->brightness < 0 || light->brightness > 1)
		return (error3(LIGHT_WAITED_VALUES, 0, 0));
	return (0);
}

int	parse_light(char **param, t_scene *scene)
{
	t_light	*light;
	int		err;

	if (valid_light_line(param))
		return (1);
	light = ft_calloc(1, sizeof(t_obj));
	if (!light)
		return (1);
	light->type = LIGHT;
	err = ft_atoi_double(&light->pos.x, param[1]);
	err |= ft_atoi_double(&light->pos.y, param[2]);
	err |= ft_atoi_double(&light->pos.z, param[3]);
	if (err)
		return (error3("Parse error: invalid number for light position", 0, 0));
	if (ft_atoi_double(&light->brightness, param[4]))
		return (error3("Parse error: invalid brightness '", param[4], "'"));
	if (ft_get_color(light, &param[5]))
		return (error3("Parse error: invalid color '", param[5], "'"));
	if (valid_values(light))
		return (1);
	ft_objadd_back(&scene->obj2, light);
	return (0);
}
