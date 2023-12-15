/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:33:27 by pepie             #+#    #+#             */
/*   Updated: 2023/11/24 11:35:50 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_hex(uintptr_t num, int is_upper)
{
	if (num >= 16)
	{
		write_hex(num / 16, is_upper);
		write_hex(num % 16, is_upper);
		return ;
	}
	if (num > 9)
	{
		if (is_upper)
			ft_putchar_fd('A' + num - 10, 1);
		else
			ft_putchar_fd('a' + num - 10, 1);
	}
	else
		ft_putchar_fd('0' + num, 1);
}

int	hex_len(uintptr_t num, t_parser *parser)
{
	int	len;

	if (parser->is_point && num == 0 && parser->dot_number == 0)
		return (0);
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

int	get_total_hex_len(unsigned int num, t_parser *parser)
{
	int	len;

	len = hex_len(num, parser);
	if (parser->is_hashtag)
		len += 2;
	return (len);
}

int	conversion_hexadecimal_lower(va_list *args, t_parser *parser)
{
	int				len;
	unsigned int	num;

	len = 0;
	num = va_arg(*args, unsigned int);
	len += handle_leading_charts_start_hex(num, parser);
	if (parser->is_hashtag && num != 0)
		len += write(1, "0x", 2);
	if (!(parser->is_point && num == 0 && parser->dot_number == 0))
	{
		write_hex(num, 0);
		len += hex_len(num, parser);
	}
	if (parser->is_dash && parser->space_number > parser->dot_number)
	{
		if (parser->dot_number > get_total_hex_len(num, parser))
			len += add_leading_chars(parser->dot_number, parser,
					parser->space_number, 0);
		else
			len += add_leading_chars(get_total_hex_len(num, parser),
					parser, parser->space_number, 0);
	}
	return (len);
}

int	conversion_hexadecimal_upper(va_list *args, t_parser *parser)
{
	int				len;
	unsigned int	num;

	len = 0;
	num = va_arg(*args, unsigned int);
	len += handle_leading_charts_start_hex(num, parser);
	if (parser->is_hashtag && num != 0)
		len += write(1, "0X", 2);
	if (!(parser->is_point && num == 0 && parser->dot_number == 0))
	{
		write_hex(num, 1);
		len += hex_len(num, parser);
	}
	if (parser->is_dash && parser->space_number > parser->dot_number)
	{
		if (parser->dot_number > get_total_hex_len(num, parser))
			len += add_leading_chars(parser->dot_number, parser,
					parser->space_number, 0);
		else
			len += add_leading_chars(get_total_hex_len(num, parser),
					parser, parser->space_number, 0);
	}
	return (len);
}
