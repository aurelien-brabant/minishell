#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "minishell/parser.h"
#include "minishell/env.h"
#include "minishell/stat.h"
#include "minishell/error.h"

#include "libft/cstring.h"
#include "libft/gc.h"
#include "libft/io.h"
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
	tmp = assert_ptr(ft_substr(word, 1, i - 1));
	var = minishell_getenv(tmp);
	free(tmp);
	if (var != NULL)
		ft_string_append_cstr(expanded, var);
	*word_loc += i;
}

static void	tokenize_var(t_vector pipeline, t_string *expanded, char *var)
{
	char	*token;
	char	*tmp;

	var = assert_ptr(ft_strdup(var));
	token = ft_strtok(var, " \t");
	tmp = token;
	while (token != NULL)
	{	
		tmp = ft_strtok(NULL, " \t");
		if (tmp == NULL)
		{
			if (token != var)
				ft_string_set_length(*expanded, 0);
			ft_string_append_cstr(*expanded, token);
		}
		else if (token == var)
		{
			ft_string_append_cstr(*expanded, token);
			parse_word(pipeline, assert_ptr(ft_string_tocstring(*expanded)));
		}
		else
			parse_word(pipeline, assert_ptr(ft_strdup(token)));
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
	while (ft_isalnum(word[i]))
		++i;
	*word_loc += i;
	if (i == 1)
		return ;
	tmp = assert_ptr(ft_substr(word, 1, i - 1));
	var = minishell_getenv(tmp);
	free(tmp);
	if (var != NULL)
		tokenize_var(pipeline, expanded, var);
}

void	expand_env_variable(t_vector pipeline, t_string *expanded,
		char **word_loc, unsigned char quote)
{
	char	status[4];

	if ((*word_loc)[1] == '?')
	{
		ft_snprintf(status, sizeof (status), "%hhu",
				stat_get()->last_status_code);
		ft_string_append_cstr(*expanded, status);
		*word_loc += 2;
	}
	else if (quote == '"')
		expand_var_in_quotes(expanded, word_loc);
	else if (!quote)
		expand_unquoted_var(pipeline, expanded, word_loc);
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
	expanded = ft_gc_add(stat_get()->tmp_gc, assert_ptr(ft_string_new
				(ft_strlen(word) * 2)), (void *)(void *)&ft_string_destroy);
	while (*word != '\0')
	{
		if (*word == quote)
			quote = 0;
		else if (!quote && (*word == '\'' || *word == '"'))
			quote = *word;
		if (quote != '\'' && word[0] == '$' && word[1] != '\0')
			expand_env_variable(pipeline, &expanded, &word, quote);
		else if (*word != '\0')
			ft_string_append_char(expanded, *word++);
	}
	if (ft_string_length(expanded) > 0)
		parse_word(pipeline, assert_ptr(ft_string_tocstring(expanded)));
}
