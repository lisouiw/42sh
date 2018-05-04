/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_brace_semicolon_split.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:50:06 by mallard           #+#    #+#             */
/*   Updated: 2018/05/04 02:35:48 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int			int_split(char *mid, int *i)
{
	int		br;

	br = 0;
	while (mid[++(*i)])
	{
		if (mid[*i] == '{')
			++br;
		else if (mid[*i] == '}')
			--br;
		if (br == 0 && mid[*i] == ',')
			return (*i);
	}
	return (*i);
}

void		free_glob_a(t_glob_a *a)
{
	t_glob_a *tmp;

	while (a->next != NULL)
	{
		tmp = a;
		a = a->next;
		free(tmp->m);
		free(tmp);
	}
	free(a->m);
	free(a);
}

t_glob_a	*add_glob_a(char *mid, t_glob_a *a)
{
	t_glob_a	*tmp;
	t_glob_a	*nw;

	tmp = a;
	if (!(nw = (t_glob_a*)malloc(sizeof(t_glob_a))))
		return (a);
	nw->m = mid;
	nw->next = NULL;
	if (a == NULL)
		return (nw);
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = nw;
	}
	return (a);
}

t_glob_a	*give_semicolon_list(char *mid, t_glob_b *b, t_glob_a *a)
{
	int			s;
	int			e;
	char		*str;

	e = 0;
	s = 0;
	while (mid[e])
	{
		str = strjoin_free_n(strjoin_free_n(b->cs,
			ft_strsub(mid, s, int_split(mid, &e) - s), 2), b->ce, 1);
		a = add_glob_a(str, a);
		s = e + 1;
	}
	return (a);
}

char		*join_list_glob_a(t_glob_a *a)
{
	char		*final;
	t_glob_a	*tmp;

	tmp = a;
	final = ft_strdup(tmp->m);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		final = strjoin_free_n(strjoin_free_n(final, " ", 1), tmp->m, 1);
	}
	return (final);
}
