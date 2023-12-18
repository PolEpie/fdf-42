/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:15:16 by pepie             #+#    #+#             */
/*   Updated: 2023/11/17 12:10:08 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*list_iter;

	if (!lst)
		return (NULL);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (NULL);
	list_iter = new_list;
	lst = lst->next;
	while (lst != NULL)
	{
		list_iter->next = ft_lstnew(f(lst->content));
		if (!list_iter->next)
		{
			ft_lstclear(&list_iter, del);
			return (NULL);
		}
		list_iter = list_iter->next;
		lst = lst->next;
	}
	return (new_list);
}
