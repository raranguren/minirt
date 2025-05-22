/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:03:43 by bduval            #+#    #+#             */
/*   Updated: 2025/05/23 00:25:29 by rarangur         ###   ########.fr       */
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
			return (PERROR2((char *)param[i], "is not valid"));
		i++;
	}
	if (i != 5)
		return (PERROR("Invalid number of parameters"));
	return (0);
}

static int	valid_values(t_light *light)
{
	if (light->brightness < 0 || light->brightness > 1)
		return (PERROR(AMB_LIGHT_WAITED_VALUES));
	return (0);
}

int	parse_amb_light(char **param, t_scene *scene, char *unique)
{
	t_light *light;

	if (*unique & AMB_LIGHT || valid_amb_line(param))
		return (1);
	*unique |= AMB_LIGHT;
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (1);
	light->type = AMB_LIGHT;
	if (ft_atoi_double(&light->brightness, param[1]))
		return (ERROR("atoi_double"));
	if (ft_get_color(&(light->color), &param[2]))
		return (ERROR("get_color"));
	if (valid_values(light))
		return (1);
	ft_objadd_back(&scene->obj, light);
	scene->amb_light = light;
	return (0);
}
