/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:50:07 by pepie             #+#    #+#             */
/*   Updated: 2023/11/09 17:34:43 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	len_str;

	len_str = 0;
	if (s == NULL)
		return ((char *)s);
	while (s[len_str])
		len_str++;
	if (start > len_str || len == 0 || len_str == 0)
		return (ft_strdup(""));
	if (len >= len_str)
		len = len_str - start;
	if (!s || len == 0)
		return (NULL);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	new_str[len] = '\0';
	while (len--)
		new_str[len] = s[start + len];
	return (new_str);
}
