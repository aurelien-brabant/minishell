/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:40:19 by abrabant          #+#    #+#             */
/*   Updated: 2021/01/04 12:13:29 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** libft implementation of strcmp(3).
**
** Compare S1 and S2, returning less than, equal to or
** greater than zero if S1 is lexicographically less than,
** equal to or greater than S2.
*/

int	ft_strcmp(const char *p1, const char *p2)
{
	const unsigned char	*s1;
	const unsigned char	*s2;

	s1 = (const unsigned char *) p1;
	s2 = (const unsigned char *) p2;
	while (*s1 == *s2 && *s1)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}
