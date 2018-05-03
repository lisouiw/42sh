/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:36:35 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:36:36 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_strncmp2(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*b1;
	unsigned char	*b2;

	i = 0;
	b1 = (unsigned char *)s1;
	b2 = (unsigned char *)s2;
	if (n == 0 || s1 == NULL || s2 == NULL)
		return (0);
	while (i < n && b1[i] == b2[i] && b1[i] != '\0' && b2[i] != '\0')
		i++;
	return (b1[i] - b2[i]);
}
