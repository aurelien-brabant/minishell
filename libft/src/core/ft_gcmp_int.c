/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcmp_uint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant </var/mail/abrabant>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:45:47 by abrabant          #+#    #+#             */
/*   Updated: 2021/03/31 15:50:00 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_gcmp_uint(void *uint1, void *uint2)
{
	unsigned int	nb1;
	unsigned int	nb2;

	nb1 = *(unsigned int *)uint1;
	nb2 = *(unsigned int *)uint2;
	if (nb1 == nb2)
		return (0);
	if (nb1 > nb2)
		return (1);
	return (-1);
}
