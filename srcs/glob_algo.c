/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:49:12 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:49:14 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		glob_cleaning(t_glob_p **parse, t_glob **g)
{
	if ((*parse)->cmd && (*parse)->cmd[0] != 47 && (*parse)->cmd[0] != '*'
		&& (*g)->cmd[(*g)->i[0]] == '\0')
		return (2);
	if ((*parse)->cmd[0] == '*')
		return (clean_star(parse, g));
	else if ((*parse)->cmd[0] == '['
		&& parse_brackets_ok((*parse)->cmd, (*parse)->i[0]))
		return (clean_brackets(g, parse));
	else if ((*parse)->cmd[0] == '?')
		return (clean_char(g, parse));
	else if ((*parse)->cmd[0] == 47)
		return (clean_dir(g, *parse));
	else
		return (clean_str(g, *parse));
	return (0);
}

int		glob_parsing_clean(t_glob **g, t_glob_p *parse)
{
	int		i;
	int		e;

	i = (*g)->i[0];
	parse->i[0] = 0;
	while (parse->next != NULL)
	{
		if ((e = glob_cleaning(&parse, g)) == 1)
		{
			(*g)->i[0] = i + 1;
			if ((*g)->cmd[(*g)->i[0]] && parse->next != NULL
				&& glob_parsing_clean(g, &(*parse)) == 0)
				return (0);
			return (1);
		}
		else if (e == 2 || e == 3)
			return (e == 2 ? 1 : 0);
		else
			i = (*g)->i[0];
		parse = parse->next;
	}
	if ((*g)->i[1] == 1 && ((*g)->i[0] > ft_strlen((*g)->cmd)
		|| (*g)->cmd[(*g)->i[0]] == '\0'))
		return (0);
	return (1);
}

t_glob	**glob_parsing_p(t_glob **g, t_glob_p *parse, int a)
{
	int		i;

	while ((*g)->next != NULL)
	{
		if (a)
			init_glob_p(&parse);
		if ((i = glob_parsing_clean(g, parse)) == 1)
			glob_free(*g);
		(*g) = (*g)->next;
	}
	return (g);
}

void	translate_glob(t_glob **g, char *s, t_glob_i y, t_cmd **ex)
{
	t_glob_p	*gp;
	char		*trad;

	gp = NULL;
	gp = glob_tab(NULL, ft_strsub(s, y.deb, y.end - y.deb));
	g = glob_parsing_p(g, gp, 1);
	trad = join_trad(*g);
	if (trad != NULL)
	{
		trad = strjoin_free_n(strjoin_free_n(ft_strsub(s, 0, y.deb), trad, 3)
			, ft_strsub(s, y.end, ft_strlen(s) - y.end), 3);
		free((*ex)->cmd);
		(*ex)->cmd = trad;
	}
	glob_p_free_list(gp);
}
