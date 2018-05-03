/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:35:25 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:35:27 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int i)
{
	char	*join;

	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!(join))
		return (NULL);
	join = ft_strcpy(join, s1);
	join = ft_strcat(join, s2);
	if (i == 1 || i == 3)
		free(s1);
	if (i == 2 || i == 3)
		free(s2);
	return (join);
}
