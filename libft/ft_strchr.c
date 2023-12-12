/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:01:27 by pepie             #+#    #+#             */
/*   Updated: 2023/11/07 14:07:03 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (((char *)s)[i])
	{
		if (((char *)s)[i] == (unsigned char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if (((char *)s)[i] == (unsigned char)c)
		return (&((char *)s)[i]);
	return (NULL);
}
