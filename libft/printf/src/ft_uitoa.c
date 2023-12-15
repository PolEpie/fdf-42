/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:39:08 by pepie             #+#    #+#             */
/*   Updated: 2023/11/17 12:34:45 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_uitoa_len(int n)
{
	unsigned int	nbr;
	int				len;

	nbr = n;
	len = 0;
	while (nbr / 10)
	{
		len++;
		nbr /= 10;
	}
	return (len + 1);
}

static char	*ft_strcat(char*dest, const char*src)
{
	int	i_dest;
	int	i_src;

	i_dest = 0;
	i_src = 0;
	while (dest[i_dest] != '\0')
	{
		i_dest++;
	}
	while (src[i_src] != '\0')
	{
		dest[i_dest + i_src] = src[i_src];
		i_src++;
	}
	dest[i_dest + i_src] = '\0';
	return (dest);
}

void	ft_uitoa_recur(int n, char *str)
{
	unsigned int	nbr;
	char			c[2];

	nbr = n;
	c[1] = '\0';
	if (nbr >= 10)
		ft_uitoa_recur(nbr / 10, str);
	c[0] = '0' + (nbr % 10);
	ft_strcat(str, c);
}

char	*ft_uitoa(unsigned int n)
{
	char			*resp;

	resp = malloc(sizeof(char) * (get_uitoa_len(n) + 1));
	if (!resp)
		return (NULL);
	*resp = 0;
	ft_uitoa_recur(n, resp);
	return (resp);
}
