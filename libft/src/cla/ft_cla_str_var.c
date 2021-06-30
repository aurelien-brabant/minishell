/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cla_str_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 22:29:40 by abrabant          #+#    #+#             */
/*   Updated: 2021/01/11 18:58:47 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft/cstring.h"
#include "libft/cla.h"
#include "libft/internal/cla_int.h"

char	*ft_cla_str_var(void *cla, char **var, const char *key
							, const char *dflt)
{
	t_cla	*cla_ptr;
	int		i;
	char	*tmp;
	char	*opt;

	cla_ptr = (t_cla *) cla;
	opt = NULL;
	i = 0;
	tmp = ft_strjoin("--", key);
	opt = ft_strjoin(tmp, "=");
	free(tmp);
	tmp = (char *)dflt;
	while (i < cla_ptr->ac)
		if (ft_strhsprfx(cla_ptr->av[i++], opt))
			tmp = ft_strchr(cla_ptr->av[i - 1], '=') + 1;
	if (var != NULL)
		*var = tmp;
	free(opt);
	return (tmp);
}
