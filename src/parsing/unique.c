/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarangur <rarangur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:51:38 by rarangur          #+#    #+#             */
/*   Updated: 2025/06/07 20:58:51 by rarangur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	unique(char obj_type, int parse_err)
{
	static char	bitmask;

	if (parse_err)
		return (parse_err);
	if (obj_type & bitmask)
		return (error("Found more than one light or camera"));
	if (0 && obj_type == LIGHT)
		return (0);
	bitmask |= obj_type;
	return (0);
}
