/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:51:34 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:51:35 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int			parse_brackets_ok(char *s, int i)
{
	int		a;

	a = i + 1;
	while (s[++i])
	{
		if (i > a && s[i] == ']')
			return (1);
	}
	return (0);
}

void		brace_int_count(int *a, int b, char *s)
{
	if (parse_brackets_ok(s, *a))
	{
		b = *a + 1;
		while (s[++(*a)])
		{
			if (s[*a] == ']' && *a > b)
			{
				(*a)++;
				return ;
			}
		}
	}
	while (s[++(*a)] && s[*a] != '[' && s[*a] != '?' && s[*a] != '*'
		&& s[*a] != 47)
		;
}

t_glob_p	*add_brace_list(t_glob_p *gp, int *st, int *end, char *s)
{
	int		a;

	a = *st;
	brace_int_count(&a, 0, s);
	while (gp && gp->next != NULL)
		gp = gp->next;
	if (gp && gp->cmd && (gp->cmd[0] == '[' || (gp->cmd[0] == '*'
		&& gp->cmd[1] == '[')))
		gp->cmd = strjoin_free_n(gp->cmd, ft_strsub(s, *st, a - *st), 3);
	else if (gp && gp->cmd && gp->cmd[0] == '*' && gp->cmd[1] == '?')
		gp = glob_p_list(gp, strjoin_free_n("*", ft_strsub(s, *st, a - *st)
			, 2));
	else
		gp = glob_p_list(gp, ft_strsub(s, *st, a - *st));
	*st = a;
	*end = a - 1;
	return (gp);
}

t_glob_p	*glob_tab(t_glob_p *gp, char *s)
{
	int		i;
	int		st;

	i = -1;
	st = 0;
	gp = NULL;
	while (s[++i] != '\0')
	{
		if (s[i] == '[' && parse_brackets_ok(s, i))
			gp = add_brace_list(gp, &st, &i, s);
		else if (s[i] == '*')
			gp = add_start_list(gp, &st, &i, s);
		else if (s[i] == '?')
			gp = add_question_list(gp, &st, &i, s);
		else if (s[i] == 47)
			gp = check_backslash_str(gp, &st, &i, s);
		else
			gp = check_match_str(gp, &st, &i, s);
	}
	if (gp)
		gp = glob_p_add_nul(gp);
	free(s);
	return (gp);
}
