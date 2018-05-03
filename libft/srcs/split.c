/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:38:29 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:38:30 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int			ft_compte(char const *s, char c)
{
	unsigned int	i;
	int				compteur;

	i = 0;
	compteur = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			compteur++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (compteur);
}

static char			**ft_split(char const *s, char c, char **str)
{
	int				i;
	int				count;
	int				count2;
	int				len;

	i = 0;
	count = 0;
	while (s[i])
	{
		count2 = 0;
		while (s[i] == c)
			i++;
		len = i;
		while (s[len] && s[len] != c)
			len++;
		if (len > i)
		{
			str[count] = (char *)malloc(sizeof(char) * (len - i + 1));
			while (i < len)
				str[count][count2++] = s[i++];
			str[count++][count2] = '\0';
		}
	}
	str[count] = NULL;
	return (str);
}

char				**split(char const *s, char c)
{
	char			**str;

	if (s == NULL)
		return (NULL);
	if (!(str = (char **)malloc(sizeof(char *) * (ft_compte(s, c) + 1))))
		return (NULL);
	return (ft_split(s, c, str));
}
