/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepie <pepie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:35:37 by pepie             #+#    #+#             */
/*   Updated: 2023/11/24 13:51:22 by pepie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>

enum e_conversion
{
	CONVERSION_ERROR = -1,
	CONVERSION_CHARACTER,
	CONVERSION_STRING,
	CONVERSION_POINTER,
	CONVERSION_DECIMAL,
	CONVERSION_INTEGER,
	CONVERSION_UNSIGNED,
	CONVERSION_HEX_LOWER,
	CONVERSION_HEX_UPPER,
	CONVERSION_PERCENT,
};

enum e_flag
{
	FLAG_ERROR = -1,
	FLAG_HASHTAG,
	FLAG_WHITESPACE,
	FLAG_PLUS,
	FLAG_ZERO,
	FLAG_NUMBER,
	FLAG_DASH,
	FLAG_DOT
};

typedef struct s_parser {
	int		conversion_type;
	bool	is_hashtag;
	bool	is_whitespace;
	bool	is_plus;
	bool	is_zero;
	bool	is_dash;
	bool	is_point;
	bool	is_negative;
	bool	minus_printed;
	bool	space_removed;
	int		space_number;
	int		dot_number;
	int		zero_number;
	int		temp;
}	t_parser;

typedef struct s_printf {
	const char	*cursor;
	int			len_printed;
}	t_printf;

char		*ft_uitoa(unsigned int n);

int			conversion_character(va_list *args, t_parser *parser);
int			conversion_string(va_list *args, t_parser *parser);
int			conversion_pointer(va_list *args, t_parser *parser);
int			conversion_int(va_list *args, t_parser *parser);
int			conversion_unsigned_int(va_list *args, t_parser *parser);
int			conversion_hexadecimal_lower(va_list *args, t_parser *parser);
int			conversion_hexadecimal_upper(va_list *args, t_parser *parser);
int			conversion_percentage(va_list *args, t_parser *parser);

enum e_flag	get_flag_type(char c);
bool		add_flag_to_parser(t_parser *parser, enum e_flag flag_type);
char		*get_number_flag(char *str, t_parser *parser, int flag_type);
void		init_parser(t_parser *parser);
int			get_num_len(int nb);
int			add_leading_chars(int num, t_parser *parser, int space, int dot);

int			handle_leading_charts_start_hex(int num, t_parser *parser);
int			get_total_hex_len(unsigned int num, t_parser *parser);

int			handle_leading_charts_end_int(t_parser *parser, int len_n);
int			get_unum_len_without_sign(unsigned int nb, t_parser *parser);
int			get_num_len_without_sign(int nb, t_parser *parser);
int			handle_leading_charts_start_int(unsigned int num, t_parser *parser);
int			get_unum_len(unsigned int nb);

int			ft_printf(const char *fmt, ...);

#endif