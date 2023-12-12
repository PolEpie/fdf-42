/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:06:18 by pepie             #+#    #+#             */
/*   Updated: 2023/11/30 13:46:39 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_freeman(t_list **list)
{
	t_list	*elem;
	t_list	*next;

	elem = *list;
	while (elem)
	{
		next = elem->next;
		free(elem->content);
		free(elem);
		elem = next;
	}
	free(list);
}

void	ft_lstadd_back(t_list **lst, char *new_content)
{
	t_list	*last;
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->content = ft_strndup(new_content, ft_strlen(new_content));
	new->next = NULL;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
	{
		last = last->next;
	}
	if (last == NULL)
		return ;
	last->next = new;
}

int	ft_lstiter(t_list *lst, int (*f)(char *))
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i += f(lst->content);
		(lst) = lst->next;
	}
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strndup(char *src, int nb)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (nb + 1));
	if (!dest)
		return (NULL);
	while (src[i] && i < nb)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
