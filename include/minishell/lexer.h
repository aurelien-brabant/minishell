#ifndef LEXER_H
# define LEXER_H
# include "minishell/datastructure.h"

typedef struct s_lexer
{
	t_stringv	*tokenv;
	size_t		current_token_index;
}	t_lexer;

typedef enum e_token_type
{
	TOKEN_ERROR = 0,
	TOKEN_WORD,
	TOKEN_REDIRECTION_OUT,
	TOKEN_REDIRECTION_IN,
	TOKEN_OR,
	TOKEN_MAX,
}	t_token_type;

/*
** character class abstraction
*/

typedef enum e_chr_class
{
	CHR_CLASS_EOL = 1,
	CHR_CLASS_DOLLAR,
	CHR_CLASS_QUOTE,
	CHR_CLASS_LEFT_ARROW,
	CHR_CLASS_RIGHT_ARROW,
	CHR_CLASS_PIPE,
	CHR_CLASS_BLANK,
	CHR_CLASS_LETTER,
	CHR_CLASS_SYMBOL,
	CHR_CLASS_DIGIT,
	CHR_CLASS_UNDEFINED,
	CHR_CLASS_MAX,
}	t_chr_class;

t_lexer			*lexer_new(void);
t_lexer			*lexer_build(char *input);
void			lexer_destroy(t_lexer *lexer);
t_token_type	token_get_type(char *token);
t_token_type	token_get(t_lexer *lexer, char **token);
t_token_type	token_get_next(t_lexer *lexer, char **token);
void			token_consume(t_lexer *lexer);

#endif
