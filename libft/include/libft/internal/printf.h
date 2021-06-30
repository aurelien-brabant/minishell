/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:21:26 by abrabant          #+#    #+#             */
/*   Updated: 2021/02/11 01:42:42 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# define PRINTF_BUF 1
# include <stdarg.h>
# include "../types.h"

/*
** The way ft_printf's internal buffer is flushed.
** FD_OUT is used by the standard ft_printf and ft_dprintf,
** while STRING_OUT is used by ft_sprintf and ft_snprintf variants.
*/

typedef enum e_out_spec
{
	STRING_OUT = 0,
	FD_OUT = 1,
}	t_out_spec;

/*
** printf conversion specifiers, i.e 'c', 's', '[id]', 'u', 'x', 'X', 'p', '%',
** 'n' (in this order).
*/

typedef enum e_spec
{
	DEFAULT_SPEC = 0,
	CHAR_SPEC = 1,
	STR_SPEC,
	INT_SPEC,
	UINT_SPEC,
	HEXLWR_SPEC,
	HEXUPR_SPEC,
	PTR_SPEC,
	PCT_SPEC,
	CUR_WRITTEN_SPEC,
	TOTAL_SPEC,
}			t_spec;

/*
** printf length specifiers, i.e 'l', 'll', 'h', 'hh' (in this order).
*/

typedef enum e_lenspec
{
	DEFAULT_LENSPEC = 0,
	L_LENSPEC = 1,
	LL_LENSPEC,
	H_LENSPEC,
	HH_LENSPEC,
}			t_lenspec;

/*
** printf flags, i.e '#', '0', '-', ' ', '+' (in this order)
*/

typedef enum e_flag
{
	DEFAULT_FLAG = 0,
	ALT_FORM_FLAG = 1 << 0,
	ZERO_PAD_FLAG = 1 << 1,
	REV_PAD_FLAG = 1 << 2,
	BLANK_FLAG = 1 << 3,
	PLUS_SIGN_FLAG = 1 << 4,
}			t_flag;

/*
** printf global state, reused by all the variants
*/

/*
** typedefs to avoid anonymous struct/union declaration, as it seems to
** cause parsing errors with the third edition of the 42 norm.
*/

/*
** Used when the converted string is to be written to a string.
*/

typedef struct s_strout
{
	long long	lim;
	char		*s;
}	t_strout;

/*
** Two outputs are actually possible:
**  - to a file descriptor
**  - to a character buffer
** This union represents the destination, which is therefore a given file
** descriptor OR a t_strout object.
*/

typedef union u_dst
{
	int			dfd;
	t_strout	strout;
}	t_dst;

/*
** The buffer used by printf to manage the output.
*/

typedef struct s_buf
{
	t_out_spec	outspec;
	size_t		len;
	char		str[PRINTF_BUF];
	t_dst		dst;
}				t_buf;

/*
** Used when converting a value.
*/

typedef struct s_conv
{
	t_spec		spec;
	t_lenspec	lenspec;
	t_byte		flags;
	int			prec;
	int			width;
	bool		isneg;
	bool		iszero;
}	t_conv;

/*
** THE ACTUAL STATE - PREVIOUS TYPEDEFS EXIST FOR IT
*/

typedef struct s_state
{
	va_list		*alst;
	const char	*fmt;
	size_t		written;
	t_buf		buf;
	t_conv		conv;
}	t_state;

/*
** Representation of a converter function
*/

typedef void(*t_converter)(t_state *);

/*
** parsing
*/

void						parse_fmt(t_state *state,
								const t_converter *converters);
/*
** buffering
*/

void						store_in_buf(t_state *s, const char *str, size_t n);
void						flush_buf(t_state *s);

/*
** conversion
*/

void						init_conv(t_converter *conv);
void						conv_int(t_state *s);
void						conv_str(t_state *s);
void						conv_char(t_state *s);
void						conv_pct(t_state *s);
void						conv_cur_written(t_state *s);

/*
** lenspec utils
*/

unsigned long long			extract_int(t_state *s);

/*
** field width
*/

void						buf_field_width(t_state *s, size_t flen);

/*
** utils
*/

bool						isflag(t_state *s, t_flag f);
void						remflag(t_state *s, t_flag f);
bool						ishexspec(t_state *s);
bool						is_int_conv(t_state *s);

#endif
