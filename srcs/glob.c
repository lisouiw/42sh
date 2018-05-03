/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:49:04 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:49:05 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		clean_brackets_star_loop(t_glob **g, char **tb, int y, int i)
{
	while (tb[++y] && (i = -1))
	{
		while (tb[y][++i])
		{
			if (tb[y][i] && tb[y][i + 1] == '-')
			{
				if ((*g)->cmd[(*g)->i[0]] >= tb[y][i]
					&& (*g)->cmd[(*g)->i[0]] <= tb[y][i + 2])
				{
					(*g)->i[0] = (*g)->i[0] + 1;
					break ;
				}
				else
					i = i + 2;
			}
			else if (tb[y][i] == (*g)->cmd[(*g)->i[0]])
			{
				(*g)->i[0] = (*g)->i[0] + 1;
				break ;
			}
		}
		if ((!tb[y][i]))
			return (1);
	}
	return (0);
}

int		check_question(char *cmd, char *s, int i, char *next)
{
	int		len;

	len = ft_strlen(cmd);
	while (len > 0 && s[i])
	{
		--len;
		++i;
	}
	if (len == 0)
	{
		if (next == NULL && s[i])
			return (1);
		return (0);
	}
	return (1);
}

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
		if ((*ex)->cmd[i] == '\\')
			i += 2;
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
