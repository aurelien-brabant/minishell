/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:16:16 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/29 01:23:04 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/internal/string_int.h"
#include "libft/string.h"
#include "libft/vector.h"
#include "libft/cstring.h"

static bool	add_to_split(t_vector split, t_string subset)
{
	if (subset == NULL)
	{
		ft_vector_destroy(split, (void (*)(void *))ft_string_destroy);
		return (false);
	}
	ft_vector_append(split, subset);
	return (true);
}

t_vector	ft_string_split(t_string str, const char *sep)
{
	t_string_int	*str_int;
	t_string		new;
	t_vector		split;
	size_t			i;
	size_t			beg;

	str_int = (t_string_int *)str;
	split = ft_vector_new(str_int->length / 2 + 1);
	if (split == NULL)
		return (NULL);
	i = 0;
	while (i < str_int->length)
	{
		while (i < str_int->length && ft_strchr(sep, str_int->chrs[i]) != NULL)
			++i;
		beg = i;
		while (i < str_int->length && ft_strchr(sep, str_int->chrs[i]) == NULL)
			++i;
		if (beg == i)
			break ;
		new = ft_string_subset(str, beg, i);
		if (!add_to_split(split, new))
			return (NULL);
	}
	return (split);
}
