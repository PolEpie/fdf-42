/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:05:19 by pepie             #+#    #+#             */
/*   Updated: 2023/11/07 14:07:29 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp( const void *pointer1, const void *pointer2, size_t size )
{
	int	i;
	int	diff;

	i = 0;
	diff = 0;
	while ((size_t)i < size)
	{
		diff = (((unsigned char *)pointer1)[i]
				- ((unsigned char *)pointer2)[i]);
		if (diff)
			return (diff);
		i++;
	}
	return (0);
}
