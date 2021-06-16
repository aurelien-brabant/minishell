#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft/io.h"
#include "libft/ctype.h"

#include "minishell/minishell.h"
#include "minishell/stat.h"

static bool	is_line_blank(const char *line)
{
	while (*line != '\0')
	{
		if (!ft_isspace(*line++))
			return (false);
	}
	return (true);
}

/*
** Present a shell prompt to the user, ready to accept a new command from
** STDIN.
** The readline GNU library is used to display a bash-like prompt with
** built-in support for history, path auto-completion, and so on.
*/

char	*prompt_present(const char *prompt)
{
	char	*line;

	line = ft_gc_add(stat_get()->tmp_gc, readline(prompt), &free);
	if (!is_line_blank(line))
		add_history(line);
	return (line);
}
