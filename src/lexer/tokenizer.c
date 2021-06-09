#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "minishell/lexer.h"
#include "minishell/stat.h"
#include "minishell/error.h"

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

size_t	get_end_of_token_index(char *str, t_token_type toktype)
{
	size_t		i;
	t_chr_class	quoted;

	i = 0;
	quoted = 0;
	while (str[i] != '\0')
	{
		if (is_quote(str[i]) && toktype == TOKEN_WORD)
			quoted = (quoted == 0) * is_quote(str[i]);
		if (!quoted && !is_chr_class_in_context(toktype, get_chr_class(str[i])))
			break ;
		++i;
	}
	return (i);
}

t_token	*get_token(char **str_loc)
{
	t_token_type	toktype;
	t_token			*token;
	size_t			end_of_token_index;

	if (**str_loc == '\0')
		return (NULL);
	while (get_chr_class(**str_loc) == CHR_CLASS_BLANK)
		(*str_loc)++;
	toktype = get_token_type(get_chr_class(**str_loc));
	end_of_token_index = get_end_of_token_index(*str_loc, toktype);	
	token = token_new(ft_substr(*str_loc, 0, end_of_token_index), toktype);
	*str_loc += end_of_token_index;
	return (token);
}
