#include <stdlib.h>
#include <unistd.h>
#include <sys/errno.h>
#include <string.h>

#include "libft/io.h"

#include "minishell/minishell.h"
#include "minishell/error.h"
#include "minishell/stat.h"

static const char	*g_error_messages[ERROR_MAX] = {
	"Dynamic memory allocation failed",
	"Found trailing pipe",
};

/*
** Print an error message on stderr and exit with exit code error + 1.
*/

int	error_print(t_error error)
{
	if (error == ERROR_ERRNO)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
		return (errno);
	}
	ft_dprintf(STDERR_FILENO, "minishell: %s\n", g_error_messages[error]);
	return (error + 1);
}

void	error_fatal(t_error error)
{
	minishell_exit(error_print(error));
}
