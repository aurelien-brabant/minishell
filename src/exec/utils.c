#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "libft/io.h"

/*
** A simple wrapper around close(2).
** Does not attempt to close a file descriptor which value is -1.
** If the address of a valid file descriptor is passed, it is closed
** and then set to -1 to indicate it has been already closed.
** The return value of close is returned.
*/

int	close_safe(int *fd)
{
	int	ret;

	ret = 0;
	if (*fd != -1)
	{
		ret = close(*fd);
		*fd = -1;
	}
	return (ret);
}

/*
** A simple wrapper around execve(2) to detect and output potential errors
** The passed arguments are the exact arguments that will be passed down to
** excecve, in the same order.
** If execve fails an error message is outputed, describing the error,
** using strerror(3).
** The process which executed execve is exited with a status of 126, which
** is reserved for execution failure.
*/

void	safe_execve(char *path, char *argv[], char *envp[])
{
	if (execve(path, argv, envp) == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", path, strerror(errno));
		free(path);
		exit(126);
	}
}

bool	file_exists(const char *filepath)
{
	struct stat	st;

	return (stat(filepath, &st) == 0);
}
