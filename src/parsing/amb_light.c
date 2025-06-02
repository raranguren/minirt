/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:03:43 by bduval            #+#    #+#             */
/*   Updated: 2025/06/02 09:57:48 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	valid_amb_line(char **param)
{
	int		i;

	i = 1;
	while (param[i])
	{
		if ((i == 1 && !ft_is_double(param[i]))
			|| (i != 1 && !ft_is_char(param[i]))
			|| i > 4)
			return (error3("Parse error : invalid '", param[i], "'"));
		i++;
	}
	if (i != 5)
		return (error3("Parse error: Wrong number of parameters", 0, 0));
	return (0);
}

static int	valid_values(t_light *light)
{
	if (light->brightness < 0 || light->brightness > 1)
		return (error3(AMB_LIGHT_WAITED_VALUES, 0, 0));
	return (0);
}

int	parse_amb_light(char **param, t_scene *scene)
{
	t_light	*light;

	if (valid_amb_line(param))
		return (1);
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (1);
	light->type = AMB_LIGHT;
	if (ft_atoi_double(&light->brightness, param[1]))
		return (error3("Parse error: invalid brightness '", param[1], "'"));
	if (ft_get_color(light, &param[2]))
		return (error3("Parse error: invalid color '", param[2], "'"));
	if (valid_values(light))
		return (1);
	ft_objadd_back(&scene->obj, light);
	return (0);
}
