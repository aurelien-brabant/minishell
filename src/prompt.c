#include <unistd.h>
#include <stdlib.h>

#include "libft/io.h"

#include "minishell/minishell.h"
#include "minishell/stat.h"

/*
** Present a shell prompt to the user, ready to accept a new command from
** STDIN.
** When the command (i.e a string of characters ending with a '\n')
** has been typed by the user, the prompt is then released and the
** prompt_present function returns the string holding the command, without
** the terminating newline character.
*/

char	*prompt_present(const char *prompt)
{
	char	*line;

	ft_putstr_fd(prompt, STDOUT_FILENO);
	if (ft_gnl(STDIN_FILENO, &line) > 0)
		;
	return (ft_gc_add(getstat()->tmp_gc, line, &free));
}
