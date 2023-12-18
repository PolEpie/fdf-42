/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:58:23 by pepie             #+#    #+#             */
/*   Updated: 2023/12/18 01:27:16 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	deg_to_rad(int angleInDegrees)
{
	return ((angleInDegrees) * M_PI / 180.0);
}

int	rad_to_deg(int angleInDegrees)
{
	return ((angleInDegrees) * 180.0 / M_PI);
}
