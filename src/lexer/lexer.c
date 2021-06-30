#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft/vector.h"
#include "libft/cstring.h"
#include "libft/gc.h"
#include "libft/io.h"

#include "minishell/lexer.h"
#include "minishell/error.h"

/*
** Character classes definition.
** 
** A character class is used as an abstraction of the standard ascii table,
** and makes tokenizing and parsing easier.
**
** For example, all ascii letters as recognized by isalpha(3) are belonging
** to the same chr_class, which is CHR_CLASS_LETTER in that case.
**
** Because an hardcoded hash table is used, it makes it really faster
** than performing calls to for example isalpha(3) all the time. It also
** allows to easily write lexer rules (see below).
*/

static const t_chr_class	g_chr_class[CHAR_MAX] = {
	/* other unprintable */

	[1] = CHR_CLASS_SYMBOL,
	[2] = CHR_CLASS_SYMBOL,
	[3] = CHR_CLASS_SYMBOL,
	[4] = CHR_CLASS_SYMBOL,
	[5] = CHR_CLASS_SYMBOL,
	[6] = CHR_CLASS_SYMBOL,
	[7] = CHR_CLASS_SYMBOL,
	[8] = CHR_CLASS_SYMBOL,
	[11] = CHR_CLASS_SYMBOL,
	[12] = CHR_CLASS_SYMBOL,
	[13] = CHR_CLASS_SYMBOL,
	[14] = CHR_CLASS_SYMBOL,
	[15] = CHR_CLASS_SYMBOL,
	[16] = CHR_CLASS_SYMBOL,
	[17] = CHR_CLASS_SYMBOL,
	[18] = CHR_CLASS_SYMBOL,
	[19] = CHR_CLASS_SYMBOL,
	[20] = CHR_CLASS_SYMBOL,
	[21] = CHR_CLASS_SYMBOL,
	[22] = CHR_CLASS_SYMBOL,
	[23] = CHR_CLASS_SYMBOL,
	[24] = CHR_CLASS_SYMBOL,
	[25] = CHR_CLASS_SYMBOL,
	[26] = CHR_CLASS_SYMBOL,
	[27] = CHR_CLASS_SYMBOL,
	[28] = CHR_CLASS_SYMBOL,
	[29] = CHR_CLASS_SYMBOL,
	[30] = CHR_CLASS_SYMBOL,
	[31] = CHR_CLASS_SYMBOL,

	['\0'] = CHR_CLASS_EOL,
	['\n'] = CHR_CLASS_EOL,

	/* BLANK */
	[' '] = CHR_CLASS_BLANK,
	['\t'] = CHR_CLASS_BLANK,

	/* OPERATOR */
	[60] = CHR_CLASS_LEFT_ARROW,
	[62] = CHR_CLASS_RIGHT_ARROW,
	[124] = CHR_CLASS_PIPE,

	/* MISC */
	['$'] = CHR_CLASS_SYMBOL,
	['~'] = CHR_CLASS_SYMBOL,

	/* QUOTES */
	['"'] = CHR_CLASS_QUOTE,
	['\''] = CHR_CLASS_QUOTE,

	/* WORD */

	['A'] = CHR_CLASS_LETTER,
	['B'] = CHR_CLASS_LETTER,
	['C'] = CHR_CLASS_LETTER,
	['D'] = CHR_CLASS_LETTER,
	['E'] = CHR_CLASS_LETTER,
	['F'] = CHR_CLASS_LETTER,
	['G'] = CHR_CLASS_LETTER,
	['H'] = CHR_CLASS_LETTER,
	['I'] = CHR_CLASS_LETTER,
	['J'] = CHR_CLASS_LETTER,
	['K'] = CHR_CLASS_LETTER,
	['L'] = CHR_CLASS_LETTER,
	['M'] = CHR_CLASS_LETTER,
	['N'] = CHR_CLASS_LETTER,
	['O'] = CHR_CLASS_LETTER,
	['P'] = CHR_CLASS_LETTER,
	['Q'] = CHR_CLASS_LETTER,
	['R'] = CHR_CLASS_LETTER,
	['S'] = CHR_CLASS_LETTER,
	['T'] = CHR_CLASS_LETTER,
	['U'] = CHR_CLASS_LETTER,
	['V'] = CHR_CLASS_LETTER,
	['W'] = CHR_CLASS_LETTER,
	['X'] = CHR_CLASS_LETTER,
	['Y'] = CHR_CLASS_LETTER,
	['Z'] = CHR_CLASS_LETTER,

	['a'] = CHR_CLASS_LETTER,
	['b'] = CHR_CLASS_LETTER,
	['c'] = CHR_CLASS_LETTER,
	['d'] = CHR_CLASS_LETTER,
	['e'] = CHR_CLASS_LETTER,
	['f'] = CHR_CLASS_LETTER,
	['g'] = CHR_CLASS_LETTER,
	['h'] = CHR_CLASS_LETTER,
	['i'] = CHR_CLASS_LETTER,
	['j'] = CHR_CLASS_LETTER,
	['k'] = CHR_CLASS_LETTER,
	['l'] = CHR_CLASS_LETTER,
	['m'] = CHR_CLASS_LETTER,
	['n'] = CHR_CLASS_LETTER,
	['o'] = CHR_CLASS_LETTER,
	['p'] = CHR_CLASS_LETTER,
	['q'] = CHR_CLASS_LETTER,
	['r'] = CHR_CLASS_LETTER,
	['s'] = CHR_CLASS_LETTER,
	['t'] = CHR_CLASS_LETTER,
	['u'] = CHR_CLASS_LETTER,
	['v'] = CHR_CLASS_LETTER,
	['w'] = CHR_CLASS_LETTER,
	['x'] = CHR_CLASS_LETTER,
	['y'] = CHR_CLASS_LETTER,
	['z'] = CHR_CLASS_LETTER,

	['0'] = CHR_CLASS_DIGIT,
	['1'] = CHR_CLASS_DIGIT,
	['2'] = CHR_CLASS_DIGIT,
	['3'] = CHR_CLASS_DIGIT,
	['4'] = CHR_CLASS_DIGIT,
	['5'] = CHR_CLASS_DIGIT,
	['6'] = CHR_CLASS_DIGIT,
	['7'] = CHR_CLASS_DIGIT,
	['8'] = CHR_CLASS_DIGIT,
	['9'] = CHR_CLASS_DIGIT,

	['.'] = CHR_CLASS_SYMBOL,
	['@'] = CHR_CLASS_SYMBOL,
	['%'] = CHR_CLASS_SYMBOL,
	['['] = CHR_CLASS_SYMBOL,
	[']'] = CHR_CLASS_SYMBOL,
	['('] = CHR_CLASS_SYMBOL,
	[')'] = CHR_CLASS_SYMBOL,
	['{'] = CHR_CLASS_SYMBOL,
	['}'] = CHR_CLASS_SYMBOL,
	['\\'] = CHR_CLASS_SYMBOL,
	['/'] = CHR_CLASS_SYMBOL,
	['*'] = CHR_CLASS_SYMBOL,
	[38] = CHR_CLASS_SYMBOL,
	['^'] = CHR_CLASS_SYMBOL,
	['-'] = CHR_CLASS_SYMBOL,
	['_'] = CHR_CLASS_SYMBOL,
	['+'] = CHR_CLASS_SYMBOL,
	['#'] = CHR_CLASS_SYMBOL,
	['='] = CHR_CLASS_SYMBOL,
	[','] = CHR_CLASS_SYMBOL,
	[';'] = CHR_CLASS_SYMBOL,
	[':'] = CHR_CLASS_SYMBOL,
	['!'] = CHR_CLASS_SYMBOL,
	['?'] = CHR_CLASS_SYMBOL,
	['`'] = CHR_CLASS_SYMBOL,
};

/*
** Determine the type of the token, usually, given its first character.
** A token can either be of type TOKEN_WORD or TOKEN_OPERATOR.
** See ressource/grammar.ebnf for more informations.
*/

static const t_token_type	g_token_type[CHR_CLASS_MAX] = {
	[CHR_CLASS_LETTER] = TOKEN_WORD,
	[CHR_CLASS_DIGIT] = TOKEN_WORD,
	[CHR_CLASS_SYMBOL] = TOKEN_WORD,
	[CHR_CLASS_DOLLAR] = TOKEN_WORD,
	[CHR_CLASS_QUOTE] = TOKEN_WORD,
	[CHR_CLASS_LEFT_ARROW] = TOKEN_REDIRECTION_IN,
	[CHR_CLASS_RIGHT_ARROW] = TOKEN_REDIRECTION_OUT,
	[CHR_CLASS_PIPE] = TOKEN_OR,
};

/*
** These are the (two) lexer rules.
** For a given token type (TOKEN_WORD | TOKEN_OPERATOR) each rule defines
** which classes of characters are still part of the token and which ones 
** are not.
**
** Boolean values are used to indicate, for each character class, if it is
** part of the current token or not. A value of 'true' means it IS, a value
** of 'false' means it IS NOT.
*/

static const bool			g_token_rules[TOKEN_MAX][CHR_CLASS_MAX] = {
	[TOKEN_WORD] = {
		[CHR_CLASS_LETTER] = true,
		[CHR_CLASS_DIGIT] = true,
		[CHR_CLASS_SYMBOL] = true,
		[CHR_CLASS_DOLLAR] = true,
		[CHR_CLASS_QUOTE] = true,
		[CHR_CLASS_LEFT_ARROW] = false,
		[CHR_CLASS_RIGHT_ARROW] = false,
		[CHR_CLASS_PIPE] = false,
		[CHR_CLASS_BLANK] = false,
		[CHR_CLASS_EOL] = false,
		[CHR_CLASS_UNDEFINED] = true,
	},
	[TOKEN_REDIRECTION_IN] = {
		[CHR_CLASS_LETTER] = false,
		[CHR_CLASS_DIGIT] = false,
		[CHR_CLASS_SYMBOL] = false,
		[CHR_CLASS_DOLLAR] = false,
		[CHR_CLASS_QUOTE] = false,
		[CHR_CLASS_LEFT_ARROW] = true,
		[CHR_CLASS_RIGHT_ARROW] = false,
		[CHR_CLASS_PIPE] = false,
		[CHR_CLASS_BLANK] = false,
		[CHR_CLASS_EOL] = false,
		[CHR_CLASS_UNDEFINED] = false,
	},
	[TOKEN_REDIRECTION_OUT] = {
		[CHR_CLASS_LETTER] = false,
		[CHR_CLASS_DIGIT] = false,
		[CHR_CLASS_SYMBOL] = false,
		[CHR_CLASS_DOLLAR] = false,
		[CHR_CLASS_QUOTE] = false,
		[CHR_CLASS_LEFT_ARROW] = false,
		[CHR_CLASS_RIGHT_ARROW] = true,
		[CHR_CLASS_PIPE] = false,
		[CHR_CLASS_BLANK] = false,
		[CHR_CLASS_EOL] = false,
		[CHR_CLASS_UNDEFINED] = false,
	},
	[TOKEN_OR] = {
		[CHR_CLASS_LETTER] = false,
		[CHR_CLASS_DIGIT] = false,
		[CHR_CLASS_SYMBOL] = false,
		[CHR_CLASS_DOLLAR] = false,
		[CHR_CLASS_QUOTE] = false,
		[CHR_CLASS_LEFT_ARROW] = false,
		[CHR_CLASS_RIGHT_ARROW] = true,
		[CHR_CLASS_PIPE] = true,
		[CHR_CLASS_BLANK] = false,
		[CHR_CLASS_EOL] = false,
		[CHR_CLASS_UNDEFINED] = false,
	},
};

t_chr_class	chr_get_class(unsigned char c)
{
	if (c > CHAR_MAX)
		return (CHR_CLASS_UNDEFINED);
	return (g_chr_class[c]);
}

t_token_type	token_get_type(char *token)
{
	if (chr_get_class(*token) == CHR_CLASS_UNDEFINED)
		return (TOKEN_WORD);
	return (g_token_type[chr_get_class(*token)]);
}

size_t	collect_token(char *input, size_t i, unsigned char *quote)
{
	t_token_type	type;

	type = token_get_type(input);
	while (chr_get_class(input[i]) != CHR_CLASS_EOL
		&& (*quote || g_token_rules[type][chr_get_class(input[i])]))
	{
		if (chr_get_class(input[i]) == CHR_CLASS_QUOTE)
		{
			if (*quote == input[i])
				*quote = 0;
			else if (!*quote && ft_strchr(input + 1, input[i]))
				*quote = input[i];
		}
		++i;
	}
	return (i);
}

t_lexer	*lexer_build(char *input)
{
	t_lexer			*lexer;
	size_t			i;
	unsigned char	quote;
	char			*token;

	i = 0;
	lexer = gc_add_tmp(lexer_new(), (void *)(void *)&lexer_destroy);
	quote = 0;
	while (chr_get_class(input[i]) != CHR_CLASS_EOL)
	{
		while (chr_get_class(input[i]) == CHR_CLASS_BLANK)
			++input;
		i = collect_token(input, i, &quote);
		if (i > 0)
		{
			token = assert_ptr(ft_substr(input, 0, i));
			assert_ptr(stringv_add(lexer->tokenv, token));
		}
		input += i;
		i = 0;
	}
	return (lexer);
}
