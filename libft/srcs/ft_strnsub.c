/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnsub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 20:06:37 by mallard           #+#    #+#             */
/*   Updated: 2018/05/02 23:35:10 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char			*ft_strnsub(char const *s, int start, int end)
{
	char		*troncon;

	troncon = (char *)malloc((sizeof(char) * (end - start)));
	if (!troncon || !s)
		return (NULL);
	while (start < end)
	{
		troncon[start] = s[start];
		start++;
	}
	troncon[end] = '\0';
	return (troncon);
}
