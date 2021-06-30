/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_csubst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 22:59:00 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/15 00:47:55 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"
#include "libft/cstring.h"
#include "libft/internal/string_int.h"

unsigned char	*istrstr(const unsigned char *chrs,
				const unsigned char *needle, size_t length)
{
	size_t	i;
	size_t	j;
	size_t	tmp;

	i = 0;
	j = 0;
	tmp = i;
	while (i < length && needle[j] != '\0'
		&& chrs[i++] == needle[j])
		++j;
	if (needle[j] == '\0')
		return ((unsigned char *)&chrs[tmp]);
	i = tmp + 1;
	return (NULL);
}

static void	append_char(const char c, t_string_int *new)
{
	char	str[2];

	str[0] = c;
	str[1] = 0;
	ft_string_append_cstr(new, str);
}

t_string_int	*ft_string_csubst(t_string str, const char *from
				, const char *to)
{
	t_string_int	*new;
	t_string_int	*si;
	size_t			i;
	unsigned char	*needlep;

	si = (t_string_int *)str;
	new = ft_string_new(si->length);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < si->length)
	{
		needlep = istrstr(&si->chrs[i], (unsigned char *)from, si->length);
		if (needlep == NULL)
			append_char(si->chrs[i++], new);
		else
		{
			ft_string_append_cstr(new, to);
			i += ft_strlen(from);
		}
	}
	return (new);
}
