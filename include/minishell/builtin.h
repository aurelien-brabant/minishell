#ifndef BUILTIN_H
# define BUILTIN_H
# include <stdbool.h>
# include <stddef.h>

typedef int	(*t_builtin)(int argc, char *argv[], bool forked);

t_builtin	builtin_get(const char *cmd_name);

/*
** BUILTINS
*/

int			builtin_env(int argc, char *argv[], bool forked);
int			builtin_cd(int argc, char *argv[], bool forked);
int			builtin_export(int argc, char *argv[], bool forked);
int			builtin_unset(int argc, char *argv[], bool forked);
int			builtin_pwd(int argc, char *argv[], bool forked);
int			builtin_echo(int argc, char *argv[], bool forked);
int			builtin_exit(int argc, char *argv[], bool forked);

#endif
