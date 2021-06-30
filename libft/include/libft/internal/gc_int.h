/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_int.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 18:42:54 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/28 22:23:05 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Garbage collector ADT internals
*/

#ifndef GC_INT_H
# define GC_INT_H
# include "libft/vector.h"

/*
** collector contains addresses that points to something that needs to be
** freed at some point. HOW it is freed must be specified by a given function
** which address is stored at the same index in the trigger vectors.
**
** A trigger function will be called like that: trigger(collected_address);
*/

typedef struct s_gc_int
{
	t_vector	collector;
	t_vector	triggers;
}	t_gc_int;

#endif
