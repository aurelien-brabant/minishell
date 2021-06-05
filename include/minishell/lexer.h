#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	TOKEN_ERROR = 0,
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_DQUOTE,
	TOKEN_SQUOTE,
	TOKEN_BLANK,
	TOKEN_MAX,
}	t_token_type;

typedef enum e_chr_class
{
	CHR_CLASS_POUND = 1,
	CHR_CLASS_NULL_BYTE,
	CHR_CLASS_DOLLAR,
	CHR_CLASS_SQUOTE,
	CHR_CLASS_DQUOTE,
	CHR_CLASS_LEFT_ARROW,
	CHR_CLASS_RIGHT_ARROW,
	CHR_CLASS_PIPE,
	CHR_CLASS_SEMICOLON,
	CHR_CLASS_BLANK,
	CHR_CLASS_WORD,
	CHR_CLASS_DIGIT,
	CHR_CLASS_MAX,
}	t_chr_class;

t_chr_class		get_chr_class(int c);	
t_token_type	get_token_type(t_chr_class chr_class);
char			*get_token(char **str_loc);

#endif
