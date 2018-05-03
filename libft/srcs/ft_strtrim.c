/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:38:02 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:38:03 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	d;
	unsigned int	f;
	char			*tab;

	if (!s)
		return (NULL);
	d = 0;
	f = ft_strlen(s);
	while (ft_isspace(s, d) != 1 && s[d] != '\0')
		d++;
	while ((int)f != 0 && ft_isspace(s, f - 1) != 1 && (int)f > 1)
		f--;
	if ((d == ft_strlen(s) && (f == 0 || f == 1)))
		return (ft_strnew(0));
	tab = ft_strsub(s, d, f - d);
	return (tab);
}
