/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:15:16 by pepie             #+#    #+#             */
/*   Updated: 2023/11/09 14:16:49 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*pointer;

	if (nitems && size && nitems > (UINT_MAX / size))
		return (NULL);
	pointer = malloc((nitems) * size);
	if (!pointer)
		return (NULL);
	ft_bzero((unsigned char *)pointer, nitems * size);
	return (pointer);
}
