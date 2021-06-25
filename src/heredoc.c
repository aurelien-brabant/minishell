#include <unistd.h>
#include <fcntl.h>

#include "minishell/minishell.h"
#include "minishell/stat.h"

#include "libft/cstring.h"

static int	here_doc_getline(char *buf)
{
	int		ret;
	size_t	i;

	i = 0;

	write(STDOUT_FILENO, "> ", 2);
	ret = read(STDIN_FILENO, &buf[i], 1);
	while (ret > 0 && buf[i] != '\n')
	{
		++i;
		ret = read(STDIN_FILENO, &buf[i], 1);
	}
	buf[i] = '\0';
	return (ret);
}

int	here_doc_prompt(const char *delim)
{
	char	buf[10000];
	int		write_fd;
	int		read_fd;

	write_fd = open(HERE_DOC_FILEPATH, O_WRONLY | O_APPEND | O_CREAT, 0664);
	read_fd = open(HERE_DOC_FILEPATH, O_RDONLY, 0664);
	while (read(read_fd, buf, 10000) > 0)
		;
	while (here_doc_getline(buf) > 0 && ft_strcmp(buf, delim) != 0)
	{
		write(write_fd, buf, ft_strlen(buf));
		write(write_fd, "\n", 1);
	}
	close(write_fd);
	return (read_fd);
}
