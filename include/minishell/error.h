#ifndef ERROR_H
# define ERROR_H

void	*assert_ptr(void *p);
void	*gc_add_tmp(void *el, void (*fn)(void *));
void	*gc_add_global(void *el, void (*fn)(void *));

#endif
