/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:44:05 by pepie             #+#    #+#             */
/*   Updated: 2023/12/15 13:34:18 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	tmp = NULL;
	i = verify_contain_nl(str, true);
	if (i < ft_strlen(str))
	{
		ft_strncat(line, str, i + 1);
		if (str[i + 1])
			tmp = ft_strndup(str + i + 1, ft_strlen(str) - i - 1);
		i = true;
	}
	else
	{
		ft_strncat(line, str, i);
		if (*buf_save != str)
			return (false);
		i = false;
	}
	free(*buf_save);
	*buf_save = tmp;
	return (i);
}

char	*parse_line(t_gnl *gnl, char **buf_save)
{
	int		len;
	char	*line;
	t_list	*elm;

	if (*buf_save == NULL && *(gnl->list) == NULL)
		return (ft_freeman(gnl, NULL));
	len = ft_strlen(*buf_save);
	if (*(gnl->list))
		len += ft_lstiter_sum(*(gnl->list), &ft_strlen);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	*line = 0;
	elm = *(gnl->list);
	if (save_on_buf(*buf_save, line, buf_save))
		return (ft_freeman(gnl, line));
	while (elm)
		(save_on_buf(elm->content, line, buf_save), elm = elm->next);
	return (ft_freeman(gnl, line));
}

char	*get_next_line(int fd)
{
	static char		*buf_save[4096];
	t_gnl			*gnl;
	int				bytes_read;

	gnl = malloc(sizeof(t_gnl));
	if (!gnl || init_gnl(gnl))
		return (NULL);
	bytes_read = 1;
	if (verify_contain_nl(buf_save[fd], false))
		return (parse_line(gnl, &buf_save[fd]));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, gnl->buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_freeman(gnl, NULL));
		gnl->buf[bytes_read] = 0;
		if (bytes_read > 0)
		{
			ft_lstadd_back_create(gnl->list, gnl->buf);
			if (verify_contain_nl(gnl->buf, false))
				break ;
		}
	}
	return (parse_line(gnl, &buf_save[fd]));
}

/* int	main(void)
{
	int	fd;
	char *line;

	fd = open("test", O_RDONLY);


	for (int i = 0; i < 20; i++)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	return (0);
} */