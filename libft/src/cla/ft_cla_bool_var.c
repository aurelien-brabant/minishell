/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cla_bool_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:26:30 by abrabant          #+#    #+#             */
/*   Updated: 2021/01/11 23:00:36 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/cstring.h"
#include "libft/cla.h"
#include "libft/internal/cla_int.h"

bool	ft_cla_bool_var(void *cla, bool *var, const char *key, const bool dflt)
{
	t_cla	*cla_ptr;
	int		i;
	char	*opt;
	bool	tmp;

	cla_ptr = (t_cla *)cla;
	opt = NULL;
	i = 0;
	opt = ft_strjoin("--", key);
	if (!opt)
		return (false);
	tmp = dflt;
	while (i < cla_ptr->ac)
		if (ft_strcmp(opt, cla_ptr->av[i++]) == 0)
			tmp = true;
	free(opt);
	if (var != NULL)
		*var = tmp;
	return (tmp);
}
