/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 03:26:27 by pepie             #+#    #+#             */
/*   Updated: 2024/10/16 14:23:06 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	is_good_input(char *str)
{
	int		i;
	bool	is_hexa;

	i = 0;
	is_hexa = false;
	if (str[0] == '0' && str[1] == 'x')
	{
		is_hexa = true;
		i = 2;
	}
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == 13
			|| (is_hexa && str[i] >= 'a' && str[i] <= 'f'))
		{
			i++;
			continue ;
		}
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-')
			return (false);
		i++;
	}
	return (true);
}

void	error_free(char **splited, char *line)
{
	ft_freesplit(splited);
	free(splited);
	free(line);
}
