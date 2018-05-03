/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_brace_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:49:25 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:49:27 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		brace_semicolon_v(char *s)
{
	int		i;
	int		v;
	int		br;

	br = 0;
	i = -1;
	v = 0;
	while (s[++i] && (s[i] != ',' || br != 0))
	{
		if (s[i] == '{' && br == 0)
			++br;
		else if (s[i] == '}' && br == 1)
			--br;
		if (br == 1 && s[i] == ',')
			++v;
	}
	if (v > 0)
		return (1);
	return (0);
}

int		check_brace(char *s, t_glob_b *b)
{
	b->s = ft_strsub(s, 0, b->deb);
	b->m = ft_strsub(s, b->deb + 1, b->end - b->deb - 2);
	b->e = ft_strsub(s, b->end, ft_strlen(s) - b->end);
	if ((brace_semicolon(b->m) && brace_semicolon_v(s)) || brace_two_comas(b))
		return (1);
	free(b->s);
	free(b->m);
	free(b->e);
	return (0);
}

int		match_brace(char *s, t_glob_b *b, int i)
{
	int		q;

	q = 1;
	b->deb = i;
	while (s[++i] && s[i] != ' ' && q != 0)
	{
		if (s[i] == '}')
			--q;
		else if (s[i] == '{')
			++q;
	}
	if (q != 0)
		return (0);
	else if (q == 0)
	{
		b->deb = b->deb;
		b->end = i;
		return (1);
	}
	return (0);
}

int		glob_brace_int(t_cmd **ex, t_glob_b *b)
{
	int		i;
	int		q;

	q = 0;
	i = -1;
	while ((*ex)->cmd[++i])
	{
		if (q != 1 && (*ex)->cmd[i] == 39)
			q = (q == 2) ? 0 : 2;
		else if (q != 2 && (*ex)->cmd[i] == '"')
			q = (q == 1) ? 0 : 1;
		else if (q == 0 && (*ex)->cmd[i] == '{' && match_brace((*ex)->cmd, b, i)
			&& check_brace((*ex)->cmd, b))
			return (i);
	}
	return (i);
}
