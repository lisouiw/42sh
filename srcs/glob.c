/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 14:11:08 by ltran             #+#    #+#             */
/*   Updated: 2018/05/02 17:00:00 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	glob(char *s, int *i, t_cmd **ex)
{
	char		*join;
	t_glob		*g;
	t_glob_i	y;

	join = NULL;
	g = NULL;
	y.deb = *i;
	while (y.deb > 0 && s[--y.deb] != ' ' && s[y.deb] != '"' && s[y.deb] != 39)
		;
	if (s[y.deb] == ' ' || s[y.deb] == '"' || s[y.deb] == 39)
		++y.deb;
	y.end = y.deb;
	while (s[y.end] && s[++y.end] != ' ' && s[y.end] != '"' && s[y.end] != 39)
		;
	join = ft_strsub(s, y.deb, y.end - y.deb);
	g = (join[0] == '.' && join[1] == '*') ? star_hide_list(g) :
		star_simple_list(g);
	free(join);
	translate_glob(&g, s, y, ex);
	glob_free_list(g);
	*i = y.end;
}

char	*glob_parsing(t_cmd **ex)
{
	int		i;
	int		q;

	i = -1;
	q = 0;
	(*ex)->cmd = glob_brace(ex);
	while ((*ex)->cmd[++i])
	{
		//if ((*ex)->cmd[i] == '\\')
		//	i++;
		if (q != 1 && (*ex)->cmd[i] == 39)
			q = (q == 2) ? 0 : 2;
		else if (q != 2 && (*ex)->cmd[i] == '"')
			q = (q == 1) ? 0 : 1;
		else if (q == 0 && ((*ex)->cmd[i] == '*' || (*ex)->cmd[i] == '['
			|| (*ex)->cmd[i] == '?'))
			glob((*ex)->cmd, &i, ex);
	}
	return ((*ex)->cmd);
}
// glob.c glob_algo.c glob_fct.c glob_fct_brackets.c glob_fct_star.c glob_free.c glob_list.c glob_list_ascii.c glob_list_p_inter.c glob_print.c glob_tab.c glob_tab_add.c glob_tab_add2.c glob_tools.c

// glob_brace_split.c glob_brace_split_alpha.c glob_brace.c glob_brace_parsing.c
// glob_brace_parsing_fct.c
