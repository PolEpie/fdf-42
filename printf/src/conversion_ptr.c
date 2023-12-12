/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:37:02 by pepie             #+#    #+#             */
/*   Updated: 2023/11/24 14:36:56 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_ptr(uintptr_t num)
{
	if (num >= 16)
	{
		write_ptr(num / 16);
		write_ptr(num % 16);
		return ;
	}
	if (num > 9)
		ft_putchar_fd('a' + num - 10, 1);
	else
		ft_putchar_fd('0' + num, 1);
}

int	ptr_len(uintptr_t num)
{
	int	len;

	len = 0;
	if (num < 16)
		return (1);
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

int	conversion_pointer(va_list *args, t_parser *parser)
{
	int			len;
	uintptr_t	addr;

	len = 0;
	addr = va_arg(*args, uintptr_t);
	if (addr <= 0)
	{	
		if (!parser->is_dash)
			len += add_leading_chars(5, parser,
					parser->space_number, parser->dot_number);
		len += write(1, "(nil)", 5);
	}
	else
	{
		if (!parser->is_dash)
			len += add_leading_chars(ptr_len(addr) + 2, parser,
					parser->space_number, parser->dot_number);
		len += write(1, "0x", 2);
		write_ptr(addr);
		len += ptr_len(addr);
	}
	if (parser->is_dash)
		len += add_leading_chars(ptr_len(addr) + 2, parser,
				parser->space_number, parser->dot_number);
	return (len);
}
