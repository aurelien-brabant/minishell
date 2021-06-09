#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#include "minishell/lexer.h"

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

static const t_chr_class	g_chr_class[UCHAR_MAX] = {
	['\0'] = CHR_CLASS_EOL, /* END OF LINE - may be modified when readline will be used instead of ft_gnl */
	['\n'] = CHR_CLASS_EOL, /* END OF LINE - may be modified when readline will be used instead of ft_gnl */

	/* BLANK */
	[' '] = CHR_CLASS_BLANK,
	['\t'] = CHR_CLASS_BLANK,

	/* OPERATOR */
	['<'] =	CHR_CLASS_LEFT_ARROW,
	['>'] =	CHR_CLASS_RIGHT_ARROW,
	['|'] =	CHR_CLASS_PIPE,

	/* MISC */
	['$'] = CHR_CLASS_DOLLAR,

	/* QUOTES */
	['"'] = CHR_CLASS_DQUOTE,
	['\''] = CHR_CLASS_SQUOTE,

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
	['&'] = CHR_CLASS_SYMBOL,
	['^'] = CHR_CLASS_SYMBOL,
	['-'] = CHR_CLASS_SYMBOL,
	['_'] = CHR_CLASS_SYMBOL,
	['+'] = CHR_CLASS_SYMBOL,
	['#'] = CHR_CLASS_SYMBOL,
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
	[CHR_CLASS_SQUOTE] = TOKEN_WORD,
	[CHR_CLASS_DQUOTE] = TOKEN_WORD,
	[CHR_CLASS_LEFT_ARROW] = TOKEN_OPERATOR,
	[CHR_CLASS_RIGHT_ARROW] = TOKEN_OPERATOR,
	[CHR_CLASS_PIPE] = TOKEN_OPERATOR,
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
		[CHR_CLASS_SQUOTE] = true,
		[CHR_CLASS_DQUOTE] = true,
		[CHR_CLASS_LEFT_ARROW] = false,
		[CHR_CLASS_RIGHT_ARROW] = false,
		[CHR_CLASS_PIPE] = false,
		[CHR_CLASS_BLANK] = false,
		[CHR_CLASS_EOL] = false,
	},
	[TOKEN_OPERATOR] = {
		[CHR_CLASS_LETTER] = false,
		[CHR_CLASS_DIGIT] = false,
		[CHR_CLASS_SYMBOL] = false,
		[CHR_CLASS_DOLLAR] = false,
		[CHR_CLASS_SQUOTE] = false,
		[CHR_CLASS_DQUOTE] = false,
		[CHR_CLASS_LEFT_ARROW] = true,
		[CHR_CLASS_RIGHT_ARROW] = true,
		[CHR_CLASS_PIPE] = true,
		[CHR_CLASS_BLANK] = false,
		[CHR_CLASS_EOL] = false,
	},
};

/*
** NOTE: about the functions defined below
**
** These functions are used to retrieve informations that are defined
** in the global variables defined in this file. As the norm requests,
** these globals are marked as static const, which means that they are
** tied to the scope of this file.
**
** In order to get these informations from anywhere the functions
** below are used.
*/

t_chr_class	get_chr_class(int c)
{
	return (g_chr_class[c]);
}

t_token_type	get_token_type(t_chr_class chr_class)
{
	return (g_token_type[chr_class]);
}

t_token_type	get_restricted_token_type(t_chr_class chr_class)
{
	return (g_token_type[chr_class]);
}

bool	is_chr_class_in_context(t_token_type toktype, t_chr_class chr_class)
{
	return (g_token_rules[toktype][chr_class]);
}
