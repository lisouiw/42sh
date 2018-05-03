/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_tab_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:51:43 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:51:43 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

t_glob_p	*check_backslash_str(t_glob_p *gp, int *st, int *end, char *trad)
{
	int		a;

	a = *st;
	while (trad[a] && trad[a] == 47)
		++a;
	gp = glob_p_list(gp, ft_strsub(trad, *st, a - *st));
	*st = a;
	*end = a - 1;
	return (gp);
}

t_glob_p	*check_match_str(t_glob_p *gp, int *st, int *end, char *trad)
{
	int		a;

	a = *st;
	while (trad[++a] && trad[a] != '[' && trad[a] != '?' && trad[a] != '*'
		&& trad[a] != 47)
		;
	while (gp && gp->next != NULL)
		gp = gp->next;
	if (gp && gp->cmd && gp->cmd[0] == '*' && gp->cmd[1] == '?')
	{
		gp->cmd = ft_strsub(gp->cmd, 1, ft_strlen(gp->cmd) - 1);
		gp = glob_p_list(gp, strjoin_free_n("*", ft_strsub(trad, *st, a - *st)
			, 2));
	}
	else
		gp = glob_p_list(gp, ft_strsub(trad, *st, a - *st));
	*st = a;
	*end = a - 1;
	return (gp);
}

t_glob_p	*add_question_list(t_glob_p *gp, int *st, int *end, char *s)
{
	int		a;
	int		b;

	a = *st;
	b = 1;
	while (s[++a] && s[a] == '?')
		;
	gp = glob_p_list(gp, ft_strsub(s, *st, a - *st));
	*st = a;
	*end = a - 1;
	return (gp);
}
