/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:40:43 by pepie             #+#    #+#             */
/*   Updated: 2023/11/09 17:36:02 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_trimmed_char(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	int		start;
	int		end;
	char	*resp;

	if (!str || !set)
		return (NULL);
	start = 0;
	end = ft_strlen((char *)str) - 1;
	while (is_trimmed_char(str[start], set) && str[start] != '\0')
		start++;
	while (is_trimmed_char(str[end], set) && end > start)
		end--;
	if (end == start && is_trimmed_char(str[start], set))
		return (ft_strdup(""));
	resp = malloc(sizeof(char) * (end - start + 2));
	if (!resp)
		return (NULL);
	ft_strlcpy(resp, (char *)&str[start], end - start + 2);
	return (resp);
}
