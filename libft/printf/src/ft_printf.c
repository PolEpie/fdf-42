/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:38:09 by pepie             #+#    #+#             */
/*   Updated: 2023/12/01 14:03:04 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

enum e_conversion	get_conversion_type(char c)
{
	if (c == 'c')
		return (CONVERSION_CHARACTER);
	else if (c == 's')
		return (CONVERSION_STRING);
	else if (c == 'p')
		return (CONVERSION_POINTER);
	else if (c == 'd')
		return (CONVERSION_DECIMAL);
	else if (c == 'i')
		return (CONVERSION_INTEGER);
	else if (c == 'u')
		return (CONVERSION_UNSIGNED);
	else if (c == 'x')
		return (CONVERSION_HEX_LOWER);
	else if (c == 'X')
		return (CONVERSION_HEX_UPPER);
	else if (c == '%')
		return (CONVERSION_PERCENT);
	else
		return (CONVERSION_ERROR);
}

void	*get_conversion_function(int type)
{
	if (type == CONVERSION_CHARACTER)
		return (conversion_character);
	else if (type == CONVERSION_STRING)
		return (conversion_string);
	else if (type == CONVERSION_POINTER)
		return (conversion_pointer);
	else if (type == CONVERSION_INTEGER
		|| type == CONVERSION_DECIMAL)
		return (conversion_int);
	else if (type == CONVERSION_UNSIGNED)
		return (conversion_unsigned_int);
	else if (type == CONVERSION_HEX_LOWER)
		return (conversion_hexadecimal_lower);
	else if (type == CONVERSION_HEX_UPPER)
		return (conversion_hexadecimal_upper);
	else if (type == CONVERSION_PERCENT)
		return (conversion_percentage);
	return (NULL);
}

int	handle_print(va_list *args, t_parser *parser)
{
	int	(*conversion_function)(va_list *args, t_parser *parser);

	if (parser->conversion_type == CONVERSION_ERROR)
		return (0);
	conversion_function = get_conversion_function(parser->conversion_type);
	if (conversion_function != NULL)
		return (conversion_function(args, parser));
	return (0);
}

void	parse_str(t_printf *prog, va_list *args, const char *str)
{
	int			conversion_type;
	int			flag_type;
	t_parser	parser;

	conversion_type = -1;
	flag_type = -1;
	parser.conversion_type = CONVERSION_ERROR;
	init_parser(&parser);
	while (*str)
	{
		conversion_type = get_conversion_type(*str);
		if (get_flag_type(*str) != -1 && get_flag_type(*str) != FLAG_NUMBER)
			flag_type = get_flag_type(*str);
		if (add_flag_to_parser(&parser, get_flag_type(*str)))
			str = get_number_flag((char *)str, &parser, flag_type) - 1;
		else if (conversion_type != CONVERSION_ERROR)
		{
			parser.conversion_type = conversion_type;
			prog->len_printed += handle_print(args, &parser);
			prog->cursor = str;
			return ;
		}
		str++;
	}
}

int	ft_printf(const char *fmt, ...)
{
	t_printf	prog;
	va_list		args;

	va_start(args, fmt);
	prog.len_printed = 0;
	prog.cursor = fmt;
	while (*prog.cursor)
	{
		if (*prog.cursor == '%' && *(prog.cursor + 1) != '\0')
		{
			parse_str(&prog, &args, prog.cursor + 1);
		}
		else
			prog.len_printed += write(1, prog.cursor, 1);
		++prog.cursor;
	}
	va_end(args);
	return (prog.len_printed);
}
