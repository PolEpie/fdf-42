/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polepie <polepie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:50:25 by pepie             #+#    #+#             */
/*   Updated: 2023/11/12 14:58:50 by polepie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_elements(const char *str, char c)
{
	int	elements_count;
	int	i;

	elements_count = 0;
	i = 0;
	while (str[i])
	{
		if (elements_count == 0 && str[i] != c)
			elements_count++;
		else if ((str[i] == c) && str[i + 1] && (str[i + 1] != c))
			elements_count++;
		i++;
	}
	return (elements_count);
}

void	init_str(char **elements, int elements_count, int len, char const *str)
{
	int		i;
	char	*element;

	i = 0;
	elements[elements_count] = malloc(sizeof(char) * (len + 1));
	element = elements[elements_count];
	if (!element)
		return ;
	while (str[i] && i < len)
	{
		element[i] = str[i];
		i++;
	}
	element[i] = '\0';
}

void	create_strings(char const *str, char c, char **elements)
{
	int	elements_count;
	int	i;
	int	a;

	elements_count = 0;
	i = 0;
	a = 0;
	while (str[a + i])
	{
		if (i != 0 && str[a + i - 1] != c && str[a + i] == c)
		{
			init_str(elements, elements_count++, i, &str[a]);
			a += i + 1;
			i = -1;
		}
		else if (str[a + i] == c)
		{
			a += i + 1;
			i = -1;
		}
		i++;
	}
	if (str[i + a] == '\0' && str[a + i - 1] != c)
		init_str(elements, elements_count++, i, &str[a]);
}

char	**ft_split(char const *str, char c)
{
	int		elements_count;
	char	**elements;

	if (!str)
		return (NULL);
	elements_count = count_elements(str, c);
	elements = malloc(sizeof(char *) * (elements_count + 1));
	if (!elements)
		return (NULL);
	if (elements_count != 0)
		create_strings(str, c, elements);
	elements[elements_count] = 0;
	return (elements);
}
