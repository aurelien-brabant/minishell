#include <stdlib.h>

#include "libft/vector.h"
#include "libft/cstring.h"

#include "minishell/parser.h"
#include "minishell/error.h"

char	*word_strip_quotes(char *word)
{
	char	*stripped;
	char	quote;
	size_t	i;

	quote = 0;
	stripped = ft_strdup(word);
	if (stripped == NULL)
		return (NULL);
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

int	parse_word(t_pipeline *pipeline, char *token)
{
	t_command	*cmd;
	t_redir		*last_redir;

	last_redir = NULL;
	cmd = &pipeline->data[pipeline->len - 1];
	if (cmd->rv->len > 0)
		last_redir = &cmd->rv->data[cmd->rv->len - 1];
	if (last_redir != NULL && last_redir->arg == NULL)
	{
		if (last_redir->type != REDIRECTION_DIN)
			token = gc_add_tmp(word_strip_quotes(token), &free);
		last_redir->arg = token;
	}
	else
		assert_ptr(stringv_add(cmd->sv,
				gc_add_tmp(word_strip_quotes(token), &free)));
	return (0);
}
