/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_suite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 22:30:19 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/28 22:59:56 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "libft/gc.h"
#include "libft/string.h"
#include "libft/vector.h"

/*
** The usefulness of a garbage collector can be seen when it comes to
** memory management, therefore it is really difficult to test here.
** The purpose of this test suite is to call the various functions,
** to make sure they work without crashing or anything.
** No leak check will be performed whatsoever.
*/

TestSuite(ft_gc_suite);

/* Test the main features of the garbage collector */

static	void wipe_split(void *el)
{
	ft_vector_destroy(el, (void (*)(void *))ft_string_destroy);
}

Test(ft_gc_suite, ft_gc_core)
{
	t_gc		gc = ft_gc_new();
	/* this line is voluntarily left as complicated to ensure its working */
	t_string	str = ft_gc_add(gc, ft_string_new_cstr("hey@@|hello|@world|@how are @you@@@@@"), (void (*)(void *))ft_string_destroy);
	t_vector		split = ft_string_split(str, "|@");

	ft_gc_add(gc, split, wipe_split);
	ft_gc_destroy(gc);
}
