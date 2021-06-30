/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_uniq.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:02:26 by abrabant          #+#    #+#             */
/*   Updated: 2021/01/04 23:00:15 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/core.h"
#include "libft/cstring.h"

/*
** Determines if *c* is found in *set*.
**
** @PARAM	c	=> the character to search for.	
** @PARAM	set	=> the set of trimmable characters, to search *c* in.
**
** @RETURN	true if *c* is found, false otherwise.
*/

static bool	is_in_set(unsigned char c, const char *set)
{
	const unsigned char	*charset;

	charset = (const unsigned char *)set;
	while (*charset)
		if (c == *charset++)
			return (true);
	return (false);
}

/*
** Get the number of characters in trimmable sequences that are going
** to be removed, in order to do a better memory allocation.
**
** @PARAM	sfront	=> the beginning of the trimmed string.
** @PARAM	sback	=> the end of the trimmed string.
** @PARAM	set		=> the set of trimmable characters.
**
** @RETURN	the number of characters that are going to be removed.
*/

static size_t	get_nb_of_inner_trimmed(const unsigned char *sfront
								, const unsigned char *sback, const char *set)
{
	unsigned char	last;
	size_t			count;

	count = 0;
	last = '\0';
	while (sfront <= sback)
	{
		if (*sfront != last)
		{
			if (is_in_set(*sfront, set))
				last = *sfront;
			else
				last = '\0';
		}
		else
			++count;
		++sfront;
	}
	return (count);
}

/*
** Write the trimmed string in *trimmed*, while reducing any sequence of
** trimmable character to only one occurence of this character.
**
** @PARAM	trimmed	=> the string that'll hold the trimmed string.
** @PARAM	sfront	=> the beginning of the trimmed string.
** @PARAM	sback	=> the end of the trimmed string.
** @PARAM	set		=> the set of trimmable characters.
*/

static void	write_uniq(unsigned char *trimmed, const unsigned char *sfront
						, const unsigned char *sback, const char *set)
{
	unsigned char	last;

	last = '\0';
	while (sfront <= sback)
	{
		if (*sfront != last)
		{
			*trimmed++ = *sfront;
			if (is_in_set(*sfront, set))
				last = *sfront;
			else
				last = '\0';
		}
		++sfront;
	}
}

/*
** Trim the string *s*. Trimmable characters must be in the set string.
** The behaviour of this function is similar to ft_strtrim: the leading
** and trailing trimmable characters are removed from the new string.
** However, this version does one more thing: if a sequence of trimmable
** characters is encountered in the string, it is reduced to only one
** occurence of this trimmable character. For example:
**
** |------------------------------------------------------------| 
** | input string:	"    Hello    world   how are   you   ?   " |
** | output string:	"Hello world how are you ?"                 | 
** |------------------------------------------------------------| 
**
** @PARAM	s	=> the string to trim.
** @PARAM	set	=> the set of characters that can be trimmed.
**
** @RETURN	the trimmed string.
*/

char	*ft_strtrim_uniq(const char *s, const char *set)
{
	const unsigned char	*sback;
	const unsigned char	*sfront;
	unsigned char		*trimmed;
	size_t				alloc_char;

	sfront = (const unsigned char *)s;
	sback = (const unsigned char *)s + (ft_strlen(s) - 1);
	while (is_in_set(*sfront, set) && sfront <= sback)
		++sfront;
	while (is_in_set(*sback, set) && sback > sfront)
		--sback;
	alloc_char = sback - sfront + !(is_in_set(*sfront, set))
		- get_nb_of_inner_trimmed(sfront, sback, set) + 1;
	trimmed = ft_calloc(alloc_char, sizeof (*trimmed));
	if (!trimmed)
		return (NULL);
	write_uniq(trimmed, sfront, sback, set);
	return ((char *) trimmed);
}
