/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:32:51 by pepie             #+#    #+#             */
/*   Updated: 2023/11/09 17:36:41 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*resp;

	if (!s || !f)
		return (NULL);
	len = ft_strlen((char *)s);
	resp = malloc(sizeof(char) * (len + 1));
	if (!resp)
		return (NULL);
	resp[len] = '\0';
	while (len--)
	{
		resp[len] = f(len, s[len]);
	}
	return (resp);
}
