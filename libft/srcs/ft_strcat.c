/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:34:02 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:34:05 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strcat(char *restrict dst, const char *restrict src)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (dst[i] != '\0')
		i++;
	while (src[c] != '\0')
	{
		dst[i] = src[c];
		i++;
		c++;
	}
	dst[i] = '\0';
	return (dst);
}
