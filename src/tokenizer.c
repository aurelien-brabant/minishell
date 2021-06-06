#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "minishell/lexer.h"

#include "libft/cstring.h"

bool	is_quote(int c)
{
	t_chr_class	chr_class;

	chr_class = get_chr_class(c);
	return (chr_class == CHR_CLASS_SQUOTE || chr_class == CHR_CLASS_DQUOTE);
}

t_token	*token_new(char *value, t_token_type toktype)
{
	t_token	*tok;

	if (value == NULL)
		return (NULL);
	tok = malloc(sizeof (*tok));
	if (tok == NULL)
		return (NULL);
	tok->value = value;
	tok->type = toktype;
	return (tok);
}

t_token	*get_token(char **str_loc)
{
	t_token_type	toktype;
	t_token			*token;
	bool			in_quotes;
	size_t			i;

	if (**str_loc == '\0')
		return (NULL);
	while (get_chr_class(**str_loc) == CHR_CLASS_BLANK)
		(*str_loc)++;
	toktype = get_token_type(get_chr_class(**str_loc));
	in_quotes = false; 
	i = 0;
	while (str_loc[0][i] != '\0')
	{
		if (is_quote(str_loc[0][i]) && toktype == TOKEN_WORD)
			in_quotes = !in_quotes;
		if (!in_quotes && !get_chr_class_context(toktype,
					get_chr_class(str_loc[0][i])))
			break ;
		++i;
	}
	if (in_quotes)
		printf("minishell: found unterminated pair of quotes\n");
	token = token_new(ft_substr(*str_loc, 0, i), toktype);
	*str_loc += i;
	return (token);
}
