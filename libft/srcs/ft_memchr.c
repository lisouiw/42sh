/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:31:34 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:31:37 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	const char		*s1;
	char			*b;

	s1 = s;
	b = (char *)s1;
	i = 0;
	while (i < n)
	{
		if (b[i] == (char)c)
			return (b + i);
		i++;
	}
	return (NULL);
}
