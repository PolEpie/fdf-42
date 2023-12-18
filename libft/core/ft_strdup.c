/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:50:07 by pepie             #+#    #+#             */
/*   Updated: 2023/11/09 14:27:27 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*retun;

	i = ft_strlen((char *)src);
	retun = malloc(sizeof(char) * (i + 1));
	if (!retun)
		return (NULL);
	*retun = '\0';
	if (i == 1)
		return (retun);
	while (i >= 0)
	{
		retun[i] = src[i];
		i--;
	}
	return (retun);
}
