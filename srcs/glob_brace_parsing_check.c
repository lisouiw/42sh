/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_brace_parsing_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 17:12:45 by ltran             #+#    #+#             */
/*   Updated: 2018/05/02 17:18:28 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		isaltwo(char *deb, char *end)
{
	if (ft_strlen(deb) != 1 || ft_strlen(end) != 1)
		return (0);
	if ((deb[0] >= 'a' || deb[0] >= 'A') && (deb[0] <= 'z' || deb[0] <= 'Z') &&
		(end[0] >= 'a' || end[0] >= 'A') && (end[0] <= 'z' || end[0] <= 'Z'))
		return (1);
	return (0);
}

int		brace_semicolon(char *s)
{
	int		i;
	int		br;

	br = 0;
	i = -1;
	while (s[++i] && (s[i] != ',' || br != 0))
	{
		if (s[i] == '{' && br == 0)
			++br;
		else if (s[i] == '}' && br == 1)
			--br;
	}
	if (s[i] == ',')
		return (1);
	return (0);
}

int		brace_two_comas(t_glob_b *b)
{
	char	*s;

	s = ft_strstr(b->m, "..");
	if (s == NULL)
		return (0);
	b->cms1 = ft_strsub(b->m, 0, ft_strlen(b->m) - ft_strlen(s));
	b->cms2 = ft_strsub(b->m, ft_strlen(b->m) - ft_strlen(s) + 2,
		ft_strlen(b->m) - ft_strlen(b->cms1) - 2);
	if ((b->cms2[0] != '\0' && b->cms1[0] != '\0' && isnumber_np(b->cms1)
		&& isnumber_np(b->cms2)))
	{
		if (b->cms1[0] == '+')
		{
			free(b->cms1);
			b->cms1 = ft_strsub(b->m, 1, ft_strlen(b->m) - ft_strlen(s) - 1);
		}
		return (1);
	}
	if (isaltwo(b->cms1, b->cms2))
		return (1);
	return (0);
}
