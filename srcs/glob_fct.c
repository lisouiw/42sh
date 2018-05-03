/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:50:34 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:50:36 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		clean_dir_plus(t_glob **g, t_glob_p *parse)
{
	t_glob	*gtmp;

	gtmp = NULL;
	gtmp = glob_path_list(gtmp, (*g)->cmd, (*g)->i[0] + 1);
	parse = parse->next;
	if (gtmp == NULL)
		return (2);
	gtmp = *glob_parsing_p(&gtmp, parse, 0);
	while (gtmp && gtmp->prev != NULL)
		gtmp = gtmp->prev;
	if (gtmp->cmd == NULL)
	{
		free(gtmp);
		return (2);
	}
	(*g) = glob_add_inter((*g), gtmp);
	return (3);
}

int		clean_dir(t_glob **g, t_glob_p *parse)
{
	DIR		*d;

	if ((parse->prev->cmd[0] != '*' && (*g)->cmd[(*g)->i[0]] != '\0')
		|| ((d = opendir((*g)->cmd)) == NULL))
		return (2);
	else
	{
		closedir(d);
		while ((*g)->cmd[(*g)->i[0]] != '\0')
			(*g)->i[0] = (*g)->i[0] + 1;
		if (parse->next->cmd != NULL)
			return (clean_dir_plus(g, parse));
		(*g)->i[1] = 1;
		return (0);
	}
	(*g)->i[1] = 0;
	return (1);
}

int		clean_str(t_glob **g, t_glob_p *parse)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen(parse->cmd);
	if ((*g)->cmd[(*g)->i[0]] == parse->cmd[parse->i[0]])
	{
		i = 1;
		while (parse->cmd[parse->i[0] + 1] && (*g)->cmd[(*g)->i[0]] &&
			(*g)->cmd[(*g)->i[0]] == parse->cmd[parse->i[0] + 1])
		{
			++i;
			parse->i[0] = parse->i[0] + 1;
		}
		(*g)->i[0] = (*g)->i[0] + i - 1;
		if (len == i)
		{
			(*g)->i[0] = (*g)->i[0] + i;
			(*g)->i[1] = 1;
			return (0);
		}
	}
	return (2);
}

int		clean_char(t_glob **g, t_glob_p **parse)
{
	int		len;

	len = ((*parse)->cmd[0] == '*') ? ft_strlen((*parse)->cmd) - 1 :
		ft_strlen((*parse)->cmd);
	while (len > 0 && (*g)->cmd[(*g)->i[0]])
	{
		--len;
		(*g)->i[0] = (*g)->i[0] + 1;
		(*parse)->i[0] = (*parse)->i[0] + 1;
	}
	if (len == 0)
	{
		if ((*parse)->next->cmd == NULL && (*parse)->cmd[0] == '*')
		{
			while ((*g)->cmd[(*g)->i[0]])
				(*g)->i[0] = (*g)->i[0] + 1;
		}
		(*g)->i[1] = 1;
		return (0);
	}
	(*g)->i[1] = 0;
	return (2);
}
