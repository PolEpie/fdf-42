/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:26:52 by pepie             #+#    #+#             */
/*   Updated: 2023/11/09 17:32:21 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char*str, char*to_find, size_t len)
{
	int	i_f;
	int	i;

	i = 0;
	if ((str == NULL && len == 0) || to_find[0] == '\0')
		return (str);
	while (str[i] != '\0' && (unsigned)i < len)
	{
		if (str[i] == to_find[0])
		{
			i_f = 0;
			while (str[i + i_f] == to_find[i_f] && to_find[i_f] != '\0'
				&& (unsigned)i + i_f < len)
			{
				i_f++;
			}
			if (to_find[i_f] == '\0')
			{
				return (&str[i]);
			}
		}
		i++;
	}
	return (NULL);
}
