/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:31:18 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:31:19 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int				ft_digit_quantity(unsigned long long n)
{
	int					ret;

	ret = 1;
	while (n >= 10)
	{
		n = n / 10;
		ret++;
	}
	return (ret);
}

static char				*create_str(char *str, int neg, unsigned long long nb)
{
	int					digits;

	digits = 0;
	digits = ft_digit_quantity(nb);
	str = ft_strnew(digits + neg);
	return (str);
}

static char				*recursive_itoa(char *str, unsigned long long nb)
{
	if (nb >= 10)
	{
		str = recursive_itoa(str, nb / 10);
		str = recursive_itoa(str + 1, nb % 10);
		return (str);
	}
	else
	{
		*str = '0' + nb;
		return (str);
	}
}

char					*ft_ltoa(long n)
{
	char				*str;
	unsigned long long	nb;
	int					negatif;

	str = NULL;
	nb = n;
	negatif = 0;
	if (n < 0)
	{
		negatif = 1;
		nb = (unsigned long long)n * -1;
	}
	str = create_str(str, negatif, nb);
	if (str == NULL)
		return (NULL);
	if (negatif)
		*str = '-';
	recursive_itoa(str + negatif, nb);
	return (str);
}
