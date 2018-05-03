/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_fct_star.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:51:00 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:51:01 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		clean_brackets_star(t_glob **g, t_glob_p **parse)
{
	char	**tb;

	tb = split_bracket(&(*parse)->cmd[1]);
	if (clean_brackets_star_loop(g, tb, -1, -1))
	{
		free_tab(tb);
		return (1);
	}
	free_tab(tb);
	if ((*parse)->next->cmd && (*parse)->next->cmd[0] == '?')
		return (check_question((*parse)->next->cmd, (*g)->cmd,
			(*g)->i[0], (*parse)->next->next->cmd));
	else if (((*parse)->next->cmd == NULL || (*parse)->next->cmd[0] == '/')
		&& (*g)->cmd[(*g)->i[0]])
		return (1);
	(*g)->i[1] = 1;
	return (0);
}

int		clean_str_star_check(t_glob **g, t_glob_p *parse, size_t i)
{
	char	*cmd;

	(*g)->i[0] = (*g)->i[0] + i;
	cmd = parse->next->next->cmd;
	if (parse->next->cmd && parse->next->cmd[0] == '?')
		return (check_question(parse->next->cmd, (*g)->cmd, (*g)->i[0], cmd));
	if ((parse->next->cmd == NULL || parse->next->cmd[0] == '/')
		&& (*g)->cmd[(*g)->i[0]])
		return (1);
	(*g)->i[1] = 1;
	return (0);
}

int		clean_str_star(t_glob **g, t_glob_p *parse)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(parse->cmd) - 1;
	if ((*g)->cmd[(*g)->i[0]] == parse->cmd[parse->i[0]])
	{
		i = 1;
		while (parse->cmd[parse->i[0] + 1] && (*g)->cmd[(*g)->i[0] + 1] &&
			(*g)->cmd[(*g)->i[0] + 1] == parse->cmd[parse->i[0] + 1])
		{
			++i;
			parse->i[0] = parse->i[0] + 1;
		}
		if (len == i)
			return (clean_str_star_check(g, parse, i));
	}
	(*g)->i[1] = 1;
	return (1);
}

int		clean_star_loop(t_glob_p **parse, t_glob **g)
{
	if ((*parse)->cmd[1] == '[')
	{
		(*parse)->i[0] = 1;
		if (clean_brackets_star(g, parse) != 1)
			return (0);
	}
	else if ((*parse)->cmd[1] == '?')
	{
		if (clean_char(g, parse) != 1)
			return (0);
	}
	else
	{
		(*parse)->i[0] = 1;
		if (clean_str_star(g, *parse) == 0)
			return (0);
	}
	return (1);
}

int		clean_star(t_glob_p **parse, t_glob **g)
{
	if ((*parse)->next->cmd == NULL && ft_strcmp((*parse)->cmd, "*") == 0)
		return (move_last_star(parse, g));
	(*parse)->i[0] = (*parse)->i[0] + 1;
	if (ft_strcmp((*parse)->cmd, "*") == 0)
		return (0);
	while ((*g)->cmd[(*g)->i[0]])
	{
		if (clean_star_loop(parse, g) == 0)
			return (0);
		(*g)->i[0] = (*g)->i[0] + 1;
	}
	(*g)->i[1] = 0;
	return (1);
}
