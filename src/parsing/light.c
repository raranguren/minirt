/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduval <bduval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 07:49:56 by bduval            #+#    #+#             */
/*   Updated: 2025/05/23 00:22:08 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	valid_light_line(char **param)
{
	int		i;

	i = 1;
	while (param[i])
	{
		if ((i <= 4  && !ft_is_double(param[i]))
			|| (i > 4 && !ft_is_char(param[i])))
			return (PERROR2((char *)param[i], "is not valid"));
		i++;
	}
	if (i != 8)
		return (PERROR("Invalid number of parameters"));
	return (0);
}

static int	valid_values(t_light *light)
{
	if (light->brightness < 0 || light->brightness > 1)
		return (PERROR(LIGHT_WAITED_VALUES));
	return (0);
}

int	parse_light(char **param, t_scene *scene, char *unique)
{
	t_light *light;

	if (*unique & LIGHT || valid_light_line(param))
		return (1);
	*unique |= LIGHT;
	light = ft_calloc(1, sizeof(t_obj));
	if (!light)
		return (1);
	light->type = LIGHT;
	if (ft_atoi_double(&light->pos.x, param[1]))
		return (ERROR("atoi_double"));
	if (ft_atoi_double(&light->pos.y, param[2]))
		return (ERROR("atoi_double"));
	if (ft_atoi_double(&light->pos.z, param[3]))
		return (ERROR("atoi_double"));
	if (ft_atoi_double(&light->brightness, param[4]))
		return (ERROR("atoi_double"));
	if (ft_get_color(&(light->color), &param[5]))
		return (ERROR("get_color"));
	if (valid_values(light))
		return (1);
	ft_objadd_back(&scene->obj, light);
	scene->light = light;
	return (0);
}
