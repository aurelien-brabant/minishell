/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cla_sanity_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:37:36 by abrabant          #+#    #+#             */
/*   Updated: 2021/01/12 00:41:36 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cstring.h"
#include "libft/io.h"
#include "libft/cla.h"
#include "libft/internal/cla_int.h"

static bool	check_max(t_cla_config *conf, int pos, char *err)
{
	if (conf->max_pos != -1 && pos > conf->max_pos)
	{
		ft_snprintf(err, 10000, conf->msg[CLA_MSG_TOO_MUCH_POS],
			conf->max_pos);
		return (false);
	}
	return (true);
}

static bool	check_arg(t_cla_config *conf, char *arg, char *err)
{
	char	**allowed;
	char	*arg_ptr;

	arg_ptr = arg;
	allowed = conf->allowed_pos;
	if (ft_strhsprfx(arg, "--"))
	{
		arg += 2;
		allowed = conf->allowed_opt;
	}
	if (allowed == NULL)
		return (true);
	while (*allowed != NULL)
		if (ft_strcmpset(*allowed++, arg, "=") == 0)
			return (true);
	ft_snprintf(err, 10000, conf->msg[CLA_MSG_FORBIDDEN_TOKEN], arg_ptr);
	return (false);
}

static bool	check_min(t_cla_config *conf, int pos, char *err)
{
	if (conf->min_pos != -1 && pos < conf->min_pos)
	{
		ft_snprintf(err, 10000, conf->msg[CLA_MSG_TOO_FEW_POS], conf->min_pos);
		return (false);
	}
	return (true);
}

bool	ft_cla_sanity_check(void *cla, t_cla_config *conf, char *err)
{
	t_cla	*cla_ptr;
	int		pos;
	int		i;

	cla_ptr = (t_cla *) cla;
	err[0] = '\0';
	i = 0;
	pos = 0;
	while (check_max(conf, pos, err) && i < cla_ptr->ac)
	{
		if (!check_arg(conf, cla_ptr->av[i], err))
			return (false);
		if (!ft_strhsprfx(cla_ptr->av[i], "--"))
			++pos;
		++i;
	}
	check_min(conf, pos, err);
	return (err[0] == '\0');
}
