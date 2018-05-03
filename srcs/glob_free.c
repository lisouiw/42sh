/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:51:06 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:51:09 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	glob_free1(t_glob *g)
{
	t_glob	*gtmp;

	gtmp = g;
	if (g->prev == NULL)
	{
		g->next = NULL;
		g->prev = NULL;
		free(g->cmd);
		free(g);
	}
	else if (g->prev != NULL)
	{
		g = g->prev;
		g->next = NULL;
		free(gtmp->cmd);
		free(gtmp);
	}
}

void	glob_free(t_glob *g)
{
	t_glob	*gtmp;

	gtmp = g;
	if (g->next == NULL)
		glob_free1(g);
	else if (g->prev != NULL)
	{
		g = g->next;
		g->prev->prev->next = g;
		g->prev = g->prev->prev;
		free(gtmp->cmd);
		free(gtmp);
	}
	else
	{
		g->next->prev = NULL;
		g = g->next;
		free(gtmp->cmd);
		free(gtmp);
	}
}

void	glob_free_list(t_glob *g)
{
	t_glob	*tmp;

	while (g->prev != NULL)
		g = g->prev;
	while (g->next != NULL)
	{
		tmp = g;
		if (g->cmd != NULL)
			g = g->next;
		free(tmp->cmd);
		free(tmp);
	}
	free(g);
}

void	glob_p_free_list(t_glob_p *g)
{
	t_glob_p	*tmp;

	while (g->prev != NULL)
		g = g->prev;
	while (g->next != NULL)
	{
		tmp = g;
		if (g->cmd != NULL)
			g = g->next;
		free(tmp->cmd);
		free(tmp);
	}
	free(g);
}
