/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 00:41:51 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/21 12:20:00 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_clamp(long long nb, long long min, long long max)
{
	if (min > max)
		return (nb);
	if (nb < min)
		return (min);
	if (nb > max)
		return (max);
	return (nb);
}
