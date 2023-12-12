/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:01:27 by pepie             #+#    #+#             */
/*   Updated: 2023/11/09 17:30:40 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char*dest, char*src, unsigned int nb)
{
	unsigned int	i_dest;
	int				i_src;
	int				total_size;

	if (dest == NULL && nb == 0)
		return (0);
	i_dest = ft_strlen(dest);
	i_src = 0;
	if (nb == 0)
		return (ft_strlen(src));
	else if (nb <= i_dest)
		return (nb + ft_strlen(src));
	total_size = i_dest + ft_strlen(src);
	while (dest[i_dest] != '\0')
	{
		i_dest++;
	}
	while (src[i_src] != '\0' && (unsigned)(i_src + i_dest + 1) < nb)
	{
		dest[i_dest + i_src] = src[i_src];
		i_src++;
	}
	dest[i_dest + i_src] = '\0';
	return (total_size);
}
