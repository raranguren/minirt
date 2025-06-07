/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:51:38 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/07 21:00:18 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	unique(char obj_type, int parse_err)
{
	static char	bitmask;

	if (parse_err)
		return (parse_err);
	if (obj_type & bitmask)
		return ("Found more than one ambient light ('A') or camera ('C')");
	if (obj_type == LIGHT)
		return (0);
	bitmask |= obj_type;
	return (0);
}
