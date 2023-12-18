/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:48:44 by pepie             #+#    #+#             */
/*   Updated: 2023/11/09 17:35:23 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char*dest, const char*src)
{
	int	i_dest;
	int	i_src;

	i_dest = 0;
	i_src = 0;
	while (dest[i_dest] != '\0')
	{
		i_dest++;
	}
	while (src[i_src] != '\0')
	{
		dest[i_dest + i_src] = src[i_src];
		i_src++;
	}
	dest[i_dest + i_src] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*resp;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = 0;
	len += ft_strlen((char *)s1);
	len += ft_strlen((char *)s2);
	resp = malloc(sizeof(char) * (len + 1));
	if (!resp)
		return (NULL);
	(*resp) = 0;
	resp = ft_strcat(resp, s1);
	resp = ft_strcat(resp, s2);
	return (resp);
}
