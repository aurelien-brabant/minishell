#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>

#include "minishell/minishell.h"
#include "minishell/stat.h"

#include "libft/cstring.h"
#include "libft/io.h"

static size_t	get_linecount(void)
{
	int		fd;
	size_t	lc;
	char	buf;

	lc = 0;
	fd = open(HERE_DOC_FILEPATH, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: could not open here document" 
				"file (%s)", strerror(errno));
		return (0);
	}
	while (read(fd, &buf, 1) > 0)
		lc += (buf == '\n');
	close(fd);
	return (lc);
}

int	here_doc_prompt(const char *delim)
{
	char	buf[10000];
	char	*line;
	int		write_fd;
	int		read_fd;

	write_fd = open(HERE_DOC_FILEPATH, O_WRONLY | O_APPEND | O_CREAT, 0664);
	read_fd = open(HERE_DOC_FILEPATH, O_RDONLY);
	while (read(read_fd, buf, 10000) > 0)
		;
	rl_replace_line("", 0);
	line = readline("> ");
	while (line != NULL && ft_strcmp(line, delim) != 0)
	{
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
		rl_on_new_line();
		line = readline("> ");
	}
	if (line == NULL)
		ft_dprintf(STDERR_FILENO, "minishell: warning: here-document at line"
			" %ld delimited by end-of-file (wanted `%s`)\n", get_linecount() + 1, delim);	
	free(line);
	close(write_fd);
	return (read_fd);
}
