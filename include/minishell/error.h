#ifndef ERROR_H
# define ERROR_H

typedef enum e_error
{
	ERROR_ERRNO = -1,
	ERROR_BADALLOC = 0,
	ERROR_TRAILING_PIPE,
	ERROR_MAX,
}	t_error;

int		error_print(t_error error);
void	error_fatal(t_error error);

#endif
