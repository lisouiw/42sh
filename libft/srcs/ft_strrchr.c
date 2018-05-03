/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:37:22 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:37:24 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*b;

	i = ft_strlen(s);
	b = (char *)s;
	while (i >= 0 && b[i] != c)
		i--;
	if (b[i] == c)
		return (&b[i]);
	return (NULL);
}
