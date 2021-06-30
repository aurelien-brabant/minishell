/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:02:13 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/26 20:34:11 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdbool.h>
# include <stddef.h>

/* abstraction */

typedef void *t_stack;

/*
** Create a new stack object of given size. The allocated capacity of the stack
** depends on the underlying container, which is a t_vector object. It is
** automatically managed and the API's user don't have/can't deal with it.
*/

t_stack	ft_stack_new(void);

/*
** Destroy a stack object, releasing all the memory allocated for it.
** As a t_vector container is used internally, the fn function is directly
** passed to the ft_vector_destroy function if required. NULL must be passed
** if no cleanup is wanted.
*/

void	ft_stack_destroy(t_stack stack, void (*fn)(void *));

/*
** Remove the element at the top of the stack and return it.
*/

void	*ft_stack_pop(t_stack stack);

/*
** Push el at the top of the stack
*/

void	ft_stack_push(t_stack stack, void *el);

/*
** Return the value at the stop of the stack without removing it
*/

void	*ft_stack_peek(t_stack stack);

/*
** Return whether the stack is empty or not. A newly initialized t_stack
** object is considered to be empty.
*/

bool	ft_stack_isempty(t_stack stack);

/*
** Return the number of elements currently in the stack
*/

size_t	ft_stack_size(t_stack stack);

#endif
