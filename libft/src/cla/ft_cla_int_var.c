/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cla_int_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 23:06:59 by abrabant          #+#    #+#             */
/*   Updated: 2021/01/11 18:56:06 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/strconv.h"
#include "libft/cstring.h"
#include "libft/cla.h"
#include "libft/internal/cla_int.h"

long long int	ft_cla_int_var(void *cla, long long int *var, const char *key
								, long long int dflt)
{
	t_cla			*cla_ptr;
	int				i;
	char			*tmp_str;
	char			*opt;
	long long int	res;

	cla_ptr = (t_cla *) cla;
	i = 0;
	opt = NULL;
	tmp_str = ft_strjoin("--", key);
	if (!tmp_str)
		return (0);
	opt = ft_strjoin(tmp_str, "=");
	if (!opt)
		return (0);
	free(tmp_str);
	res = dflt;
	while (i < cla_ptr->ac)
		if (ft_strhsprfx(cla_ptr->av[i++], opt))
			res = ft_btoll(ft_strchr(cla_ptr->av[i - 1], '=') + 1, 10);
	if (var != NULL)
		*var = res;
	free(opt);
	return (res);
}
