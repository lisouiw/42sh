/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_tab_add2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:51:49 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:51:51 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void		add_start_list_parse(int *a, char *s)
{
	int		b;

	b = 1;
	if (s[*a] == '[')
		brace_int_count(a, b, s);
	else if (s[(*a)] == '?')
	{
		while (s[++(*a)] && s[*a] == '?')
			;
	}
	else if (s[*a] != '[' && s[*a] != '?' && s[*a] != '*' && s[*a] != 47)
	{
		while (s[++(*a)] && s[*a] != '[' && s[*a] != '?' && s[*a] != '*'
			&& s[*a] != 47)
			;
	}
}

t_glob_p	*add_start_list(t_glob_p *gp, int *st, int *end, char *s)
{
	int		a;

	a = *st;
	while (s[++a] && s[a] == '*')
		;
	*st = a - 1;
	if (s[a] == '\0')
	{
		*st = a;
		*end = a - 1;
		return (glob_p_list(gp, ft_strdup("*")));
	}
	else
		add_start_list_parse(&a, s);
	gp = glob_p_list(gp, ft_strsub(s, *st, a - *st));
	*st = a;
	*end = a - 1;
	return (gp);
}
