#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#include "minishell/lexer.h"

static const	t_chr_class	g_chr_class[UCHAR_MAX] = {
	['\0'] = CHR_CLASS_NULL_BYTE,

	/* METACHARACTERS - SEPARATE WORDS */
	[' '] = CHR_CLASS_BLANK,
	['\t'] = CHR_CLASS_BLANK,
	['<'] =	CHR_CLASS_RIGHT_ARROW,
	['>'] =	CHR_CLASS_RIGHT_ARROW,
	['|'] =	CHR_CLASS_PIPE,
	[';'] = CHR_CLASS_SEMICOLON,

	/* MISC */

	['#'] = CHR_CLASS_POUND,
	['$'] = CHR_CLASS_DOLLAR,

	/* QUOTES */
	['"'] = CHR_CLASS_DQUOTE,
	['\''] = CHR_CLASS_SQUOTE,

	/* WORDS */
	['A'] = CHR_CLASS_WORD,
	['B'] = CHR_CLASS_WORD,
	['C'] = CHR_CLASS_WORD,
	['D'] = CHR_CLASS_WORD,
	['E'] = CHR_CLASS_WORD,
	['F'] = CHR_CLASS_WORD,
	['G'] = CHR_CLASS_WORD,
	['H'] = CHR_CLASS_WORD,
	['I'] = CHR_CLASS_WORD,
	['J'] = CHR_CLASS_WORD,
	['K'] = CHR_CLASS_WORD,
	['L'] = CHR_CLASS_WORD,
	['M'] = CHR_CLASS_WORD,
	['N'] = CHR_CLASS_WORD,
	['O'] = CHR_CLASS_WORD,
	['P'] = CHR_CLASS_WORD,
	['Q'] = CHR_CLASS_WORD,
	['R'] = CHR_CLASS_WORD,
	['S'] = CHR_CLASS_WORD,
	['T'] = CHR_CLASS_WORD,
	['U'] = CHR_CLASS_WORD,
	['V'] = CHR_CLASS_WORD,
	['W'] = CHR_CLASS_WORD,
	['X'] = CHR_CLASS_WORD,
	['Y'] = CHR_CLASS_WORD,
	['Z'] = CHR_CLASS_WORD,

	['a'] = CHR_CLASS_WORD,
	['b'] = CHR_CLASS_WORD,
	['c'] = CHR_CLASS_WORD,
	['d'] = CHR_CLASS_WORD,
	['e'] = CHR_CLASS_WORD,
	['f'] = CHR_CLASS_WORD,
	['g'] = CHR_CLASS_WORD,
	['h'] = CHR_CLASS_WORD,
	['i'] = CHR_CLASS_WORD,
	['j'] = CHR_CLASS_WORD,
	['k'] = CHR_CLASS_WORD,
	['l'] = CHR_CLASS_WORD,
	['m'] = CHR_CLASS_WORD,
	['n'] = CHR_CLASS_WORD,
	['o'] = CHR_CLASS_WORD,
	['p'] = CHR_CLASS_WORD,
	['q'] = CHR_CLASS_WORD,
	['r'] = CHR_CLASS_WORD,
	['s'] = CHR_CLASS_WORD,
	['t'] = CHR_CLASS_WORD,
	['u'] = CHR_CLASS_WORD,
	['v'] = CHR_CLASS_WORD,
	['w'] = CHR_CLASS_WORD,
	['x'] = CHR_CLASS_WORD,
	['y'] = CHR_CLASS_WORD,
	['z'] = CHR_CLASS_WORD,

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

	['.'] = CHR_CLASS_WORD,
	['@'] = CHR_CLASS_WORD,
	['%'] = CHR_CLASS_WORD,
	['['] = CHR_CLASS_WORD,
	[']'] = CHR_CLASS_WORD,
	['('] = CHR_CLASS_WORD,
	[')'] = CHR_CLASS_WORD,
	['{'] = CHR_CLASS_WORD,
	['}'] = CHR_CLASS_WORD,
	['\\'] = CHR_CLASS_WORD,
	['/'] = CHR_CLASS_WORD,
	['*'] = CHR_CLASS_WORD,
	['&'] = CHR_CLASS_WORD,
	['^'] = CHR_CLASS_WORD,
	['-'] = CHR_CLASS_WORD,
	['_'] = CHR_CLASS_WORD,
	['+'] = CHR_CLASS_WORD,
};

static const t_token_type	g_token_type[CHR_CLASS_MAX] = {
	[CHR_CLASS_BLANK] = TOKEN_BLANK,
	[CHR_CLASS_WORD] = TOKEN_WORD,
	[CHR_CLASS_DIGIT] = TOKEN_WORD,
	[CHR_CLASS_DOLLAR] = TOKEN_WORD,
	[CHR_CLASS_SQUOTE] = TOKEN_SQUOTE,
	[CHR_CLASS_DQUOTE] = TOKEN_DQUOTE,
	[CHR_CLASS_POUND] = TOKEN_OPERATOR,
	[CHR_CLASS_LEFT_ARROW] = TOKEN_OPERATOR,
	[CHR_CLASS_RIGHT_ARROW] = TOKEN_OPERATOR,
	[CHR_CLASS_PIPE] = TOKEN_OPERATOR,
	[CHR_CLASS_SEMICOLON] = TOKEN_OPERATOR,
};

static const	bool	g_token_rules[TOKEN_MAX][CHR_CLASS_MAX] = {
	[TOKEN_WORD] = {
		[CHR_CLASS_WORD] = 1,
		[CHR_CLASS_DIGIT] = 1,
		[CHR_CLASS_DOLLAR] = 1,
		[CHR_CLASS_SQUOTE] = 1,
		[CHR_CLASS_DQUOTE] = 1,
		[CHR_CLASS_POUND] = 1,
		[CHR_CLASS_LEFT_ARROW] = 0,
		[CHR_CLASS_RIGHT_ARROW] = 0,
		[CHR_CLASS_PIPE] = 0,
		[CHR_CLASS_BLANK] = 0,
		[CHR_CLASS_SEMICOLON] = 0,
		[CHR_CLASS_NULL_BYTE] = 0,
	},
	[TOKEN_OPERATOR] = {
		[CHR_CLASS_WORD] = 0,
		[CHR_CLASS_DIGIT] = 0,
		[CHR_CLASS_DOLLAR] = 0,
		[CHR_CLASS_SQUOTE] = 0,
		[CHR_CLASS_DQUOTE] = 0,
		[CHR_CLASS_POUND] = 0,
		[CHR_CLASS_LEFT_ARROW] = 1,
		[CHR_CLASS_RIGHT_ARROW] = 1,
		[CHR_CLASS_PIPE] = 1,
		[CHR_CLASS_BLANK] = 0,
		[CHR_CLASS_SEMICOLON] = 1,
		[CHR_CLASS_NULL_BYTE] = 0,
	},
	[TOKEN_DQUOTE] = {
		[CHR_CLASS_WORD] = 1,
		[CHR_CLASS_DIGIT] = 1,
		[CHR_CLASS_DOLLAR] = 1,
		[CHR_CLASS_SQUOTE] = 1,
		[CHR_CLASS_DQUOTE] = 0,
		[CHR_CLASS_POUND] = 1,
		[CHR_CLASS_LEFT_ARROW] = 1,
		[CHR_CLASS_RIGHT_ARROW] = 1,
		[CHR_CLASS_PIPE] = 1,
		[CHR_CLASS_BLANK] = 1,
		[CHR_CLASS_NULL_BYTE] = 0,
	},
	[TOKEN_SQUOTE] = {
		[CHR_CLASS_WORD] = 1,
		[CHR_CLASS_DIGIT] = 1,
		[CHR_CLASS_DOLLAR] = 1,
		[CHR_CLASS_SQUOTE] = 0,
		[CHR_CLASS_DQUOTE] = 1,
		[CHR_CLASS_POUND] = 1,
		[CHR_CLASS_LEFT_ARROW] = 1,
		[CHR_CLASS_RIGHT_ARROW] = 1,
		[CHR_CLASS_PIPE] = 1,
		[CHR_CLASS_BLANK] = 1,
		[CHR_CLASS_NULL_BYTE] = 0,
	},
	[TOKEN_BLANK] = {
		[CHR_CLASS_DIGIT] = 0,
		[CHR_CLASS_DOLLAR] = 0,
		[CHR_CLASS_SQUOTE] = 0,
		[CHR_CLASS_DQUOTE] = 0,
		[CHR_CLASS_POUND] = 0,
		[CHR_CLASS_LEFT_ARROW] = 0,
		[CHR_CLASS_RIGHT_ARROW] = 0,
		[CHR_CLASS_PIPE] = 0,
		[CHR_CLASS_BLANK] = 0,
		[CHR_CLASS_NULL_BYTE] = 0,
	},
};

t_chr_class	get_chr_class(int c)
{
	return (g_chr_class[c]);
}

t_token_type	get_token_type(t_chr_class chr_class)
{
	return (g_token_type[chr_class]);
}

bool	get_chr_class_context(t_token_type toktype, t_chr_class chr_class)
{
	return (g_token_rules[toktype][chr_class]);
}
