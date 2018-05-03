/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:36:18 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:36:19 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strncat(char *restrict dst, const char *restrict src, size_t n)
{
	unsigned int	i;
	unsigned int	c;

	i = ft_strlen(dst);
	c = 0;
	while (c < n && src[c] != '\0')
		dst[i++] = src[c++];
	dst[i++] = '\0';
	return (dst);
}
