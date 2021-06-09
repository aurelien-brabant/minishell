#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	TOKEN_ERROR = 0,
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_MAX,
}	t_token_type;

/*
** character class abstraction
*/

typedef enum e_chr_class
{
	CHR_CLASS_EOL = 1,
	CHR_CLASS_DOLLAR,
	CHR_CLASS_SQUOTE,
	CHR_CLASS_DQUOTE,
	CHR_CLASS_LEFT_ARROW,
	CHR_CLASS_RIGHT_ARROW,
	CHR_CLASS_PIPE,
	CHR_CLASS_BLANK,
	CHR_CLASS_LETTER,
	CHR_CLASS_SYMBOL,
	CHR_CLASS_DIGIT,
	CHR_CLASS_MAX,
}	t_chr_class;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}	t_token;

t_token_type	get_restricted_token_type(t_chr_class chr_class);
t_chr_class		get_chr_class(int c);	
t_token_type	get_token_type(t_chr_class chr_class);
bool			is_chr_class_in_context(t_token_type toktype,
					t_chr_class chr_class);
t_token			*get_token(char **input);

#endif
