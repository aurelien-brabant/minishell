#include <stdio.h>
#include <stdlib.h>

#include "libft/cstring.h"
#include "libft/ctype.h"

void	expand_var_in_quotes(char **expanded_ptr, char **word_loc)
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
	if (var == NULL)
		return ;
	tmp = *expanded_ptr;
	*expanded_ptr = ft_strjoin(*expanded_ptr, var);
}

void	expand(char *word)
{
	char			*expanded;
	char			*expanded_ptr;
	unsigned char	quote;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	quote = 0;
	expanded = "";
	expanded_ptr = expanded;
	while (*word != '\0')
	{
		if (*word == quote)
			quote = 0;
		else if (*word == '\'' || *word == '"')
			quote = *word;
		if (*word == '$' && *word != '\'')
		{
			if (quote == '"')
				expand_var_in_quotes(&expanded_ptr, &word);
			break ;
		}
		++word;
	}
	printf("Expanded to => %s\n", expanded_ptr);
}
