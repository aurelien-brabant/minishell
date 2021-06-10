#ifndef LEXER_H
# define LEXER_H
# include "libft/vector.h"

typedef struct	t_lexer
{
	t_vector	tokenv;
	size_t		current_token_index;
}	t_lexer;

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

t_lexer			*lexer_build(char *input);
char			*token_get(t_lexer *lexer);
t_token_type	token_get_type(char *token);
char			*token_get_next(t_lexer *lexer);
void			token_consume(t_lexer *lexer);

#endif
