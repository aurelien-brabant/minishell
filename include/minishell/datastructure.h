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
/*                             COMMANDS                                      */
/*****************************************************************************/

/*
** For convenience only, each command keeps its own id, that is the index
** of it in the command vector.
*/

typedef struct s_command
{
	size_t		id;
	t_redirv	*redirv;
	char		**argv;
}	t_command;

typedef struct s_commandv
{
	size_t		cap;
	size_t		len;
	t_command	*data;
}	t_commandv;

/*
** Initialize a new command vector, made to hold every command that the shell
** will need to process.
** Each command object is initialized by making a call to redirv_new, there is
** no need to manually initialize the redirection vector attached to a given
** command.
**/

t_commandv	commandv_new(size_t cap);

/*
** Add a new command to the command vector.
** Only the address of the command vector is required and nothing else.
** A command does not need to have a name, because a command can only
** be made of redirections.
**
** The address of the added command is returned.
*/

t_commandv	commandv_add(t_commandv *cmdv);

void		commandv_destroy(t_commandv *cmdv);

#endif
