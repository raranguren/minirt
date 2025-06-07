/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:00:15 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/07 14:09:02 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_get_map_name(char **dest, char *param)
{
	if (!param)
	{
		*dest = NULL;
		return (0);
	}
	*dest = ft_strdup(param);
	if (!dest)
		return (-1);
	return (0);
}
