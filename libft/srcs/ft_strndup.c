/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corosteg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 13:16:58 by corosteg          #+#    #+#             */
/*   Updated: 2018/04/22 20:00:31 by paoroste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*ft_strndup(char *s, int len)
{
	char	*result;
	int		i;

	i = 0;
	len = (size_t)len;
	if (ft_strlen(s) < (size_t)len)
		len = ft_strlen(s);
	if (!(result = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
