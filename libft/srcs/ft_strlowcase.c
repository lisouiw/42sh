/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:35:55 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:35:56 by mallard          ###   ########.fr       */
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
