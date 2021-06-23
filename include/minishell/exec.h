#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

void	exec(t_vector parsed);
char	*get_pwd(void);


/* UTILS */
void	free_tab(char **tab);
void	print_tab(char **tab);
int		tab_len(char **tab);

#endif
