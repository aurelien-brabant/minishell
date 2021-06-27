#ifndef DATASTRUCTURE_H
# define DATASTRUCTURE_H
# include <stddef.h>

/*****************************************************************************/
/*                             REDIRECTIONS                                  */
/*****************************************************************************/

typedef enum e_redir_type
{
	REDIRECTION_NONE = -1,
	REDIRECTION_OUT,
	REDIRECTION_IN,
	REDIRECTION_DIN,
	REDIRECTION_DOUT,
	REDIRECTION_MAX,
}	t_redir_type;

typedef struct s_redir
{
	char			*arg;
	t_redir_type	type;
}	t_redir;

/*
** redir vector
*/

typedef struct s_redirv
{
	size_t	len;
	size_t	cap;
	t_redir	*data;
}	t_redirv;

/*
** Create a new redirection vector.
** An array of *cap* redir objects is created, and will be populated by
** successive calls to redirv_add.
** This array will be automatically resized if needed.
*/

t_redirv	*redirv_new(size_t cap);

/*
** Add a new element to the specified redirection vector, increasing its
** length by one.
*/

t_redir		*redirv_add(t_redirv *redirv, t_redir_type type);

/*
** Destroy a redirection vector.
*/

void		redirv_destroy(t_redirv *redirv);	

/*****************************************************************************/
/*                             STRING VECTOR                                 */
/*****************************************************************************/

typedef struct s_stringv
{
	size_t	cap;
	size_t	len;
	char	**data;
}	t_stringv;

/*
** Initialize a new string vector.
** For convenience and to make it easy to work with execve, the internal
** string array stored in a string vector is always NULL terminated while
** that's not the case for the vectors implemented above.
*/

t_stringv	*stringv_new(size_t cap);

/*
** Add the string str to the string vector.
**
** The string which is passed as an argument is returned.
*/

char		*stringv_add(t_stringv *sv, char *str);

/*
** Delete string at index i in the string vector.
** A delete function is required to work with minishell environment
** easily, as the environment is represented using a string vector.
*/

void		stringv_del(t_stringv *sv, size_t i);

void		stringv_destroy(t_stringv *sv);

#endif

/*****************************************************************************/
/*                             COMMANDS                                      */
/*****************************************************************************/

# define REDIRV_DEFAULT_CAP 5
# define STRINGV_DEFAULT_CAP 5

/*
** For convenience only, each command keeps its own id, that is the index
** of it in the command vector.
*/

typedef struct s_command
{
	size_t		id;
	t_redirv	*rv;
	t_stringv	*sv;
}	t_command;

typedef struct s_pipeline
{
	size_t		cap;
	size_t		len;
	t_command	*data;
}	t_pipeline;

/*
** Initialize a new command vector, made to hold every command that the shell
** will need to process.
** Each command object is initialized by making a call to redirv_new, there is
** no need to manually initialize the redirection vector attached to a given
** command.
**/

t_pipeline	*pipeline_new(size_t cap);

/*
** Add a new command to the command vector.
** Only the address of the command vector is required and nothing else.
** A command does not need to have a name, because a command can only
** be made of redirections.
**
** The address of the added command is returned.
*/

t_command	*pipeline_add(t_pipeline *pipeline, size_t id);

void		pipeline_destroy(t_pipeline *pipeline);

