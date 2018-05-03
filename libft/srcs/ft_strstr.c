/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:37:42 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:37:44 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	char *a;
	char *b;

	if (*little == '\0')
		return ((char *)big);
	while (*big)
	{
		a = (char *)big;
		b = (char *)little;
		while (*b && *a == *b)
		{
			a++;
			b++;
		}
		if (*b == '\0')
			return ((char *)big);
		big++;
	}
	return (NULL);
}
