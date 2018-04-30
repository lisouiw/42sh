/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paoroste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 22:44:34 by paoroste          #+#    #+#             */
/*   Updated: 2018/04/22 19:56:32 by paoroste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strlowcase(char *str)
{
	char	*new;
	int		i;

	i = 0;
	if ((new = ft_strdup(str)) == NULL)
		return (NULL);
	while (new[i] != '\0')
	{
		if (new[i] >= 'A' && new[i] <= 'Z')
			new[i] = new[i] + 32;
		i++;
	}
	return (new);
}
