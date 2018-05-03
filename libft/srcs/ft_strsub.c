/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:37:50 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:37:51 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*troncon;

	i = 0;
	troncon = (char *)ft_memalloc((sizeof(char) * (len + 1)));
	if (!troncon || !s)
		return (NULL);
	while (i < len)
	{
		troncon[i] = s[start];
		i++;
		start++;
	}
	troncon[len] = '\0';
	return (troncon);
}
