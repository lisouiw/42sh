/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:32:02 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:32:03 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	char			*d;
	const char		*s;

	i = 1;
	d = dst;
	s = src;
	while (i <= n && s < d)
	{
		d[n - i] = s[n - i];
		i++;
	}
	i = 0;
	while (i < n && s >= d)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
