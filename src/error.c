#include <stdlib.h>
#include <unistd.h>

#include "libft/io.h"

#include "minishell/error.h"
#include "minishell/stat.h"

static const char	*g_error_messages[ERROR_MAX] = {
	"Dynamic memory allocation failed",
	"Found unterminated quotation",
	"Found trailing pipe",
};

/*
** Print an error message on stderr and exit with exit code error + 1.
*/

int	error_print(t_error error)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s\n", g_error_messages[error]);
	return (error + 1);
}
