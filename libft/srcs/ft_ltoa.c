/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:41:23 by mallard           #+#    #+#             */
/*   Updated: 2018/04/10 16:12:41 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*ft_ltoa(long int nbr)
{
	char	*str;
	int		i;

	i = ft_llen(nbr) - 1;
	if (nbr == -9223372036854775807 - 1)
		return (ft_strdup("-9223372036854775808"));
	if (nbr == 0)
		return (ft_strdup("0"));
	if (!(str = ft_strnew(i)))
		exit(1);
	if (nbr < 0)
	{
		i--;
		nbr = nbr * -1;
		str[0] = '-';
	}
	while (i >= 0)
	{
		str[i] = (nbr % 10) + '0';
		nbr/=10;
		i--;
	}
	return (str);
}
