#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	i = 0;
	while (word[i] != '"' && !ft_isspace(word[i]))
		++i;
	tmp = ft_substr(word, 1, i - 1);
	var = getenv(tmp);
	free(tmp);
	if (var != NULL)
		ft_string_append_cstr(expanded, var);
	*word_loc += i;
}

void	expand(char *word)
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
		else if (*word == '\'' || *word == '"')
			quote = *word;
		if (*word == '$' && *word != '\'')
		{
			if (quote == '"')
				expand_var_in_quotes(expanded, &word);
		}
		ft_string_append_char(expanded, *word++);
	}
	ft_string_output(expanded, STDOUT_FILENO);
}
