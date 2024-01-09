/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:06:18 by pepie             #+#    #+#             */
/*   Updated: 2023/12/18 13:38:16 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_freeman(t_gnl *gnl, char *ret)
{
	t_list	*elem;
	t_list	*next;

	elem = *(gnl->list);
	while (elem)
	{
		next = elem->next;
		free(elem->content);
		free(elem);
		elem = next;
	}
	free(gnl->buf);
	free(gnl->list);
	free(gnl);
	return (ret);
}

void	ft_lstadd_back_create(t_list **lst, char *new_content)
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

int	ft_lstiter_sum(void *lst, int (*f)(char *))
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i += f(((t_list *)lst)->content);
		(lst) = ((t_list *)lst)->next;
	}
	return (i);
}

int	init_gnl(t_gnl *gnl)
{
	gnl->list = malloc(sizeof(t_list *));
	if (!(gnl->list))
		return (1);
	*(gnl->list) = NULL;
	gnl->buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(gnl->buf))
		return (1);
	return (0);
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
