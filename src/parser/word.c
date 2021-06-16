#include <stdlib.h>

#include "libft/vector.h"
#include "libft/cstring.h"

#include "minishell/parser.h"

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

void	parse_word(t_vector pipeline, char *token)
{
	t_command		*cmd;
	t_redirection	*last_out_redir;

	token = word_strip_quotes(token);	
	last_out_redir = NULL;
	cmd = ft_vector_get(pipeline, ft_vector_length(pipeline) - 1);
	if (ft_vector_length(cmd->redir_out) > 0)
		last_out_redir = ft_vector_get(cmd->redir_out, ft_vector_length(cmd->redir_out) - 1);
	if (cmd->redir_in && cmd->redir_in->arg == NULL)
		cmd->redir_in->arg = token;
	else if (last_out_redir && last_out_redir->arg == NULL)
		last_out_redir->arg = token;
	else
		argv_append(cmd->argv, token);
}
