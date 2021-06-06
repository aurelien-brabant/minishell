#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	TOKEN_ERROR = 0,
	TOKEN_WORD,
	TOKEN_OPERATOR,
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
	CHR_CLASS_BACKSLASH,
	CHR_CLASS_AND,
	CHR_CLASS_LBRACKET,
	CHR_CLASS_RBRACKET,
	CHR_CLASS_LPARENS,
	CHR_CLASS_RPARENS,
	CHR_CLASS_LBRACE,
	CHR_CLASS_RBRACE,
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
bool			get_chr_class_context(t_token_type toktype,
					t_chr_class chr_class);
t_token			*get_token(char **input);

#endif
