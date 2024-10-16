/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 23:58:23 by pepie             #+#    #+#             */
/*   Updated: 2024/10/16 14:25:10 by pepie            ###   ########.fr       */
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

void	free_row(void *list)
{
	t_map	**lst;
	int		i;

	i = 0;
	lst = list;
	while (lst[i])
	{
		free(lst[i]);
		i++;
	}
	free(lst);
}
