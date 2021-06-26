#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>

#include "minishell/minishell.h"
#include "minishell/stat.h"
#include "minishell/error.h"
#include "minishell/env.h"

#include "libft/string.h"
#include "libft/cstring.h"
#include "libft/io.h"
#include "libft/ctype.h"

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

static void	expand_var(t_string *str, char **line_loc)
{
	size_t	i;
	char	*line;
	char	*var_name;
	char	*var_val;

	i = 0;
	line = *line_loc;
	var_val = NULL;
	while (ft_isalnum(line[i]))
		++i;	
	var_name = ft_substr(line, 0, i);
	if (var_name != NULL)
		var_val = minishell_getenv(var_name);
	if (var_val != NULL)
		ft_string_append_cstr(*str, var_val);
	*line_loc += i - 1; 
}

static char	*expand_line(char *line)
{
	t_string	str;
	char		*expanded;

	str = ft_string_new(ft_strlen(line));
	while (*line != '\0')
	{
		if (*line == '$' && line[1] != '\0')
		{
			++line;
			expand_var(&str, &line);
		}
		else
			ft_string_append_char(str, *line);
		++line;
	}
	expanded = ft_string_tocstring(str);
	ft_string_destroy(str);
	return (expanded);
}

static void	prepare_fds(int fd[2])
{
	char	buf[10000];

	fd[1] = open(HERE_DOC_FILEPATH, O_WRONLY | O_APPEND | O_CREAT, 0664);
	fd[0] = open(HERE_DOC_FILEPATH, O_RDONLY);
	while (read(fd[0], buf, 10000) > 0)
		;
}

int	here_doc_prompt(const char *delim)
{
	bool	disable_expansion;
	char	*line;
	int		fd[2];

	prepare_fds(fd);
	disable_expansion = (*delim == '\'' || *delim == '"')
		&& delim[ft_strlen(delim) - 1] == *delim;
	if (disable_expansion)
		delim = assert_ptr(word_strip_quotes((char *)delim));
	line = readline("> ");
	while (line != NULL && ft_strcmp(line, delim) != 0)
	{
		if (!disable_expansion)
			line = assert_ptr(expand_line(line));
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	write(fd[1], "\n", 1);
	if (line == NULL)
		ft_dprintf(2, "minishell: warning: here-document at line %ld delimited"
				"by end-of-file (wanted `%s`)\n", get_linecount(), delim);	
	free(line);
	close(fd[1]);
	return (fd[0]);
}
