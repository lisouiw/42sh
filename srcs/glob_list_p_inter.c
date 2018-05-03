/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_list_p_inter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:51:27 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:51:28 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

t_glob		*glob_add_inter_prev(t_glob **g, t_glob **gtmp)
{
	t_glob	*t1;
	t_glob	*t2;

	t1 = *g;
	g = gtmp;
	while ((*gtmp)->next->cmd != NULL)
		*gtmp = (*gtmp)->next;
	t2 = (*gtmp)->next;
	t1->next->prev = (*gtmp);
	(*gtmp)->next = t1->next;
	free(t1->cmd);
	free(t1);
	free(t2->cmd);
	free(t2);
	return (*gtmp);
}

t_glob		*glob_add_inter(t_glob *g, t_glob *gtmp)
{
	t_glob	*t1;
	t_glob	*t2;

	while (gtmp->prev != NULL)
		gtmp = gtmp->prev;
	if (g->prev == NULL)
		return (glob_add_inter_prev(&g, &gtmp));
	else
	{
		t1 = g;
		g->prev->next = gtmp;
		gtmp->prev = g->prev;
		while (gtmp->next->cmd != NULL)
			gtmp = gtmp->next;
		t2 = gtmp->next;
		t1->next->prev = gtmp;
		gtmp->next = t1->next;
		free(t1->cmd);
		free(t1);
		free(t2->cmd);
		free(t2);
		return (gtmp);
	}
	return (g);
}

t_glob_p	*glob_p_add_nul(t_glob_p *gp)
{
	t_glob_p	*new;
	t_glob_p	*tmp;

	tmp = gp;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (!(new = (t_glob_p*)malloc(sizeof(t_glob_p))))
		return (NULL);
	new->cmd = NULL;
	new->i[0] = 0;
	new->i[1] = 0;
	new->prev = NULL;
	new->next = NULL;
	tmp->next = new;
	new->prev = tmp;
	return (gp);
}

t_glob_p	*glob_p_list(t_glob_p *gp, char *trad)
{
	t_glob_p	*new;
	t_glob_p	*tmp;

	tmp = gp;
	if (!(new = (t_glob_p*)malloc(sizeof(t_glob_p))))
		return (NULL);
	new->cmd = trad;
	new->i[0] = 0;
	new->i[1] = 0;
	new->prev = NULL;
	new->next = NULL;
	if (gp == NULL)
		return (new);
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (gp);
}
