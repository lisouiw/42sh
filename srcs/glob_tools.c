/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:51:57 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:51:59 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

char	*join_trad(t_glob *g)
{
	char	*trad;

	while (g->prev != NULL)
		g = g->prev;
	if (g->cmd != NULL)
		trad = strdup(g->cmd);
	else
		return (NULL);
	g = g->next;
	while (g->next != NULL)
	{
		trad = strjoin_free_n(trad, ft_strjoin(" ", g->cmd), 3);
		g = g->next;
	}
	return (trad);
}

void	init_glob_p(t_glob_p **parse)
{
	while ((*parse)->next->cmd != NULL)
		*parse = (*parse)->next;
	while ((*parse)->prev != NULL)
	{
		(*parse)->i[0] = 0;
		*parse = (*parse)->prev;
	}
	(*parse)->i[0] = 0;
}

int		move_last_star(t_glob_p **parse, t_glob **g)
{
	while ((*g)->cmd[(*g)->i[0]])
	{
		(*parse)->i[0] = (*parse)->i[0] + 1;
		(*g)->i[0] = (*g)->i[0] + 1;
	}
	(*g)->i[1] = 1;
	return (0);
}
