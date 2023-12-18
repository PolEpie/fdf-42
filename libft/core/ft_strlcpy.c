/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:51:42 by pepie             #+#    #+#             */
/*   Updated: 2023/11/09 14:45:41 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char*dest, char*src, unsigned int size)
{
	unsigned int	src_size;

	if (size == 0)
	{
		return (ft_strlen(src));
	}
	src_size = 0;
	while (src[src_size] != '\0' && src_size < size - 1)
	{
		dest[src_size] = src[src_size];
		src_size++;
	}
	dest[src_size] = '\0';
	return (ft_strlen(src));
}
