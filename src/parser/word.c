#include <stdlib.h>

#include "libft/vector.h"
#include "libft/cstring.h"

#include "minishell/parser.h"
#include "minishell/error.h"

/*
char	*word_strip_quotes(char *word)
{
	unsigned char	quote;
	char			*stripped;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	stripped = ft_strdup(word);
	quote = 0;
	while (word[j] != '\0')
	{
		if (word[j] == quote)
			quote = 0;
		else if (!quote && (word[j] == '\'' || word[j] == '"'))
			quote = word[j];
		else if (word[j] != quote)
			stripped[i++] = word[j];
		++j;
	}
	stripped[i] = '\0';
	return (stripped);
}
*/

char	*word_strip_quotes(char *word)
{
	char	*stripped;
	char	quote;
	size_t	i;

	quote = 0;
	stripped = assert_ptr(ft_strdup(word));
	i = 0;
	while (*word != '\0')
	{
		if (*word == quote)
			quote = 0;
		else if (!quote && (*word == '\'' || *word == '\"') 
				&& ft_strchr(word + 1, *word))
			quote = *word; 
		else
			stripped[i++] = *word;
		++word;
	}
	stripped[i] = '\0';
	return (stripped);
}

/*
** Quotes are not stripped for here document (<< redirection) because they
** are needed to determine if variable expansion will be done or not.
*/

int	parse_word(t_vector pipeline, char *token)
{
	t_command		*cmd;
	t_redirection	*last_redir;

	cmd = ft_vector_get(pipeline, ft_vector_length(pipeline) - 1);
	last_redir = ft_vector_last(cmd->redir);
	if (last_redir && last_redir->arg == NULL)
	{
		if (last_redir->type != REDIRECTION_DIN)
			token = word_strip_quotes(token);
		last_redir->arg = token;
	}
	else
		argv_append(cmd->argv, word_strip_quotes(token));
	return (0);
}
