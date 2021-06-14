#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "minishell/parser.h"

#include "libft/cstring.h"
#include "libft/string.h"
#include "libft/ctype.h"

void	expand_var_in_quotes(t_string expanded, char **word_loc)
{
	char	*word;
	char	*var;
	char	*tmp;
	size_t	i;
	
	word = *word_loc;
	i = 1;
	while (ft_isalnum(word[i]))
		++i;
	tmp = ft_substr(word, 1, i - 1);
	var = getenv(tmp);
	free(tmp);
	if (var != NULL)
		ft_string_append_cstr(expanded, var);
	*word_loc += i;
}

static void	tokenize_var(t_vector pipeline, t_string *expanded, char *var)
{
	char	*token;
	char	*tmp;

	var = ft_strdup(var);
	token = ft_strtok(var, " \t");
	tmp = token;
	while (token != NULL)
	{	
		tmp = ft_strtok(NULL, " \t");
		if (tmp == NULL)
		{
			*expanded = ft_string_new(10);
			ft_string_append_cstr(*expanded, token);
		}
		else if (token == var)
		{
			ft_string_append_cstr(*expanded, token);
			parse_word(pipeline, ft_string_tocstring(*expanded));
		}
		else
			parse_word(pipeline, ft_strdup(token));
		
		token = tmp;
	}
}

void	expand_unquoted_var(t_vector pipeline, t_string *expanded, char **word_loc)
{
	char	*word;
	char	*var;
	char	*tmp;
	size_t	i;
	
	word = *word_loc;
	i = 1;
	while (ft_isalnum(word[i]) && !ft_isspace(word[i]))
		++i;
	tmp = ft_substr(word, 1, i - 1);
	var = getenv(tmp);
	free(tmp);
	*word_loc += i;
	if (var != NULL)
		tokenize_var(pipeline, expanded, var);
}

void	expand(t_vector pipeline, char *word)
{
	t_string		expanded;
	unsigned char	quote;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	quote = 0;
	expanded = ft_string_new(ft_strlen(word) * 2);
	while (*word != '\0')
	{
		if (*word == quote)
			quote = 0;
		else if (!quote && (*word == '\'' || *word == '"'))
			quote = *word;
		if (*word == '$' && *word != '\'')
		{
			if (quote == '"')
				expand_var_in_quotes(expanded, &word);
			if (!quote)
				expand_unquoted_var(pipeline, &expanded, &word);
		}
		else if (*word != '\0')
			ft_string_append_char(expanded, *word++);
	}
	parse_word(pipeline, ft_string_tocstring(expanded));
}
