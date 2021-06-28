#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "minishell/minishell.h"
#include "minishell/exec.h"

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
	if (isdir(path) || execve(path, argv, envp) == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", path, strerror(errno));
		minishell_exit(126);
	}
}

bool	file_exists(const char *filepath)
{
	struct stat	st;

	return (stat(filepath, &st) == 0);
}

void	close_pipes(int *pipefd, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		close_safe(&(pipefd + (i * 2))[0]);
		close_safe(&(pipefd + (i * 2))[1]);
		++i;
	}
}

/*
 ** Returns whether or not filepath is a path pointing to a directory.
 ** If it is the case, the errno variable is ensured to be set to EISDIR after
 ** isdir has returned. It may seem kinda weird for a function such as isdir,
 ** but it can become really handly while doing error handling.
 */

bool	isdir(const char *filepath)
{
	int		fd;
	int		old_errno;
	bool	ret;

	ret = false;
	old_errno = 0;
	fd = open(filepath, O_RDONLY);
	if (fd != -1 && read(fd, NULL, 0) == -1)
	{
		old_errno = errno;
		ret = errno == EISDIR;
	}
	errno = old_errno;
	close_safe(&fd);
	return (ret);
}
