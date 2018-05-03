/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:37:11 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:37:12 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int j;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (big[i] != '\0' && len >= (size_t)ft_strlen((char *)little) && len--)
	{
		j = 0;
		while (big[i + j] == little[j] && big[i + j] && little[j])
		{
			j++;
			if (little[j] == '\0')
				return ((char *)big + i);
		}
		i++;
	}
	if (little[0] == '\0')
		return ((char *)big + i);
	return (NULL);
}
