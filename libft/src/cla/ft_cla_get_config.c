/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cla_get_config.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 22:50:41 by abrabant          #+#    #+#             */
/*   Updated: 2021/01/12 00:02:33 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/cla.h"

/*
** Get the default configuration structure.
*/

t_cla_config	ft_cla_get_config(void)
{
	t_cla_config	conf;

	conf.msg[CLA_MSG_TOO_MUCH_POS] = "Too much arguments: expected at most %d";
	conf.msg[CLA_MSG_TOO_FEW_POS] = "Too few arguments: expected at least %d";
	conf.msg[CLA_MSG_FORBIDDEN_TOKEN] = "Forbidden token: \"%s\"";
	conf.min_pos = -1;
	conf.max_pos = -1;
	conf.allowed_pos = NULL;
	conf.allowed_opt = NULL;
	return (conf);
}
