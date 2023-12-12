/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:42:39 by pepie             #+#    #+#             */
/*   Updated: 2023/12/02 21:08:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10000000
#endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_list {
	void			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);

void	ft_lstadd_back(t_list **lst, char *n);
int		ft_strlen(char *str);
int		ft_lstiter(t_list *lst, int (*f)(char *));
char	*ft_strndup(char *src, int nb);
void	ft_freeman(t_list **list);
#endif