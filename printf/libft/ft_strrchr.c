/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:01:27 by pepie             #+#    #+#             */
/*   Updated: 2023/11/07 14:08:42 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (((char *)s)[i])
		i++;
	while (i > 0)
	{
		if (((char *)s)[i] == (unsigned char)c)
			return (&((char *)s)[i]);
		i--;
	}
	if (((char *)s)[i] == (unsigned char)c)
		return (&((char *)s)[i]);
	return (NULL);
}
