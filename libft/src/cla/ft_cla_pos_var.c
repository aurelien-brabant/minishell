/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cla_pos_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:27:04 by abrabant          #+#    #+#             */
/*   Updated: 2021/01/11 18:57:52 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cstring.h"
#include "libft/io.h"

#include "libft/internal/cla_int.h"

char	*ft_cla_pos_var(void *cla, char **var, int index, const char *dflt)
{
	t_cla	*cla_ptr;
	int		i;
	char	*res;

	cla_ptr = (t_cla *) cla;
	i = 0;
	res = (char *)dflt;
	while (i < cla_ptr->ac)
	{
		if (!ft_strhsprfx(cla_ptr->av[i], "--"))
			if (index-- == 0)
				break ;
		++i;
	}
	if (index == -1 && i < cla_ptr->ac)
		res = cla_ptr->av[i];
	if (var != NULL)
		*var = res;
	return (res);
}
