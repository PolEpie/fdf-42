/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:37:43 by pepie             #+#    #+#             */
/*   Updated: 2023/11/24 11:24:30 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conversion_character(va_list *args, t_parser *parser)
{
	char	c;
	int		len;

	len = 0;
	c = va_arg(*args, int);
	if (!parser->is_dash)
		len += add_leading_chars(1, parser, parser->space_number,
				parser->dot_number);
	len += write(1, &c, 1);
	if (parser->is_dash)
		len += add_leading_chars(1, parser, parser->space_number,
				parser->dot_number);
	return (len);
}

int	handle_null(t_parser *parser)
{
	int	len;

	len = 0;
	if (!parser->is_dash)
		len += add_leading_chars(6, parser, parser->space_number,
				parser->dot_number);
	if (parser->is_point)
	{
		if ((unsigned long)parser->dot_number > 6)
			len += write(1, "(null)", 6);
		else
			len += write(1, "(null)", parser->dot_number);
	}
	else
		len += write(1, "(null)", 6);
	if (parser->is_dash)
		len += add_leading_chars(6, parser, parser->space_number,
				parser->dot_number);
	return (len);
}

int	get_str_len_real(char *str, t_parser *parser)
{
	if (parser->is_point)
	{
		if ((unsigned long)parser->dot_number <= ft_strlen(str))
			return (parser->dot_number);
	}
	return (ft_strlen(str));
}

int	conversion_string(va_list *args, t_parser *parser)
{
	char	*str;
	int		len;

	len = 0;
	str = va_arg(*args, char *);
	if (!str)
		return (handle_null(parser));
	if (!parser->is_dash)
		len += add_leading_chars(get_str_len_real(str, parser), parser,
				parser->space_number, parser->dot_number);
	len += write(1, str, get_str_len_real(str, parser));
	if (parser->is_dash)
		len += add_leading_chars(get_str_len_real(str, parser), parser,
				parser->space_number, parser->dot_number);
	return (len);
}

int	conversion_percentage(va_list *args, t_parser *parser)
{
	int	len;

	len = 0;
	(void)(args);
	if (!parser->is_dash)
	{
		if (parser->is_zero && parser->is_point)
			len += add_leading_chars(1, parser, parser->zero_number,
					parser->dot_number);
		else
			len += add_leading_chars(1, parser, parser->space_number,
					parser->dot_number);
	}
	len += write(1, "%", 1);
	if (parser->is_dash)
		len += add_leading_chars(1, parser, parser->space_number,
				parser->dot_number);
	return (len);
}
