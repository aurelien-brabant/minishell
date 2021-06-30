/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:50:40 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/28 22:22:14 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

/* abstraction */
typedef void *t_gc;

/*
** Initialize a new garbage collector.
*/

t_gc	ft_gc_new(void);

/*
** Add el to the garbage collector, and specifiy the address of the function
** used for el's cleanup. This trigger function will be called with el
** passed as only argument.
**
** el is returned for convenience only.
*/

void	*ft_gc_add(t_gc gc, void *el, void (*trigger)());

/*
** Wipe all the elements which have been added in the garbage colllector.
** NOTE: this function doesn't DESTROY the garbage collector, it only
** performs a complete wipe and makes it empty. Useful if memory needs to
** be released at some point without destroying the garbage collector.
**
** The first element in the garbage collector will be wiped first.
*/

void	*ft_gc_wipe(t_gc gc);

/*
** Destroy the garbage collector, making it unusable for future uses.
** Calls ft_gc_wipe before.
** Often used at the end of a program.
*/

void	ft_gc_destroy(t_gc gc);

#endif
