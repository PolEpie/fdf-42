/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:44:05 by pepie             #+#    #+#             */
/*   Updated: 2023/12/02 21:23:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	verify_contain_nl(char *buf, bool get_index)
{
	int	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			if (get_index)
				return (i);
			return (1);
		}
		i++;
	}
	if (get_index)
		return (i);
	return (0);
}

static char	*ft_strncat(char*dest, char*src, unsigned int nb)
{
	int	i_dest;
	int	i_src;

	i_dest = 0;
	i_src = 0;
	while (dest[i_dest] != '\0')
	{
		i_dest++;
	}
	while (src[i_src] != '\0' && (unsigned)i_src < nb)
	{
		dest[i_dest + i_src] = src[i_src];
		i_src++;
	}
	dest[i_dest + i_src] = '\0';
	return (dest);
}

bool	save_on_buf(char *str, char *line, char **buf_save)
{
	int		i;
	char	*tmp;

	if (!str)
		return (false);
	if (verify_contain_nl(str, false) == 0)
	{
		i = ft_strncat(line, str, ft_strlen(str)) == NULL;

		if (*buf_save == str)
		{
			free(*buf_save);
			*buf_save = NULL;
		}
		return (i);
	}
	else
	{
		i = verify_contain_nl(str, true);
		if (i < ft_strlen(str))
		{
			ft_strncat(line, str, i + 1);
			if (str[i + 1])
			{
				tmp = ft_strndup(str + i + 1, ft_strlen(str) - i - 1);
				if (*buf_save != NULL)
					free(*buf_save);
				*buf_save = tmp;
			}
			else
			{
				if (*buf_save != NULL)
					free(*buf_save);
				*buf_save = NULL;
				return (true);
			}
		}
		else
		{
			ft_strncat(line, str, i);
		}
		return (true);
	}
}

char	*parse_line(t_list **lst, char **buf_save)
{
	int		len;
	char	*line;
	t_list	*elm;
	bool	is_save;

	if (*buf_save == NULL && *lst == NULL)
	{
		free(lst);
		return (NULL);
	}
	len = ft_strlen(*buf_save);
	if (*lst)
		len += ft_lstiter(*lst, &ft_strlen);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	*line = 0;
	elm = *lst;
	is_save = save_on_buf(*buf_save, line, buf_save);
	if (is_save)
	{
		ft_freeman(lst);
		return (line);
	}
	while (elm)
	{
		is_save = save_on_buf(elm->content, line, buf_save);
		//printf("buf_save = |%s|\n", *buf_save);
		elm = elm->next;
	}
	ft_freeman(lst);
	//write(1, "COUCOU", 6);
	return (line);
}

char	*get_next_line(int fd)
{
	static	char	*buf_save[4096];
	char			*buf;
	bool			contain_nl;
	t_list			**lst;
	int				bytes_read;

	lst = malloc(sizeof(t_list *));
	if (!lst)
		return (NULL);
	(*lst) = NULL;
	contain_nl = 0;
	if (verify_contain_nl(buf_save[fd], false))
		return (parse_line(lst, &buf_save[fd]));
	bytes_read = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (contain_nl == 0 && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			free(lst);
			return (NULL);
		}
		buf[bytes_read] = 0;
		if (bytes_read > 0)
		{
			ft_lstadd_back(lst, buf);
			contain_nl = verify_contain_nl(buf, false);
		}
	}
	free(buf);
	return (parse_line(lst, &buf_save[fd]));
}

/* int	main(void)
{
	int	fd;
	char *line;

	fd = open("test", O_RDONLY);


	for (int i = 0; i < 2; i++)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	return (0);
} */
