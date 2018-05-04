/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatmt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:56:56 by mallard           #+#    #+#             */
/*   Updated: 2018/05/04 03:58:37 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		init_treatmt(t_cmd **ex, t_edit **cmd, t_froz **fz)
{
	*ex = NULL;
	while ((*cmd)->rpz[0] == 0)
		*cmd = (*cmd)->next;
	if ((*fz)->nb[0] % g_nb->tb[0] != 1)
		ft_putchar('\n');
	if ((*fz)->mode[3] != 6 && (*fz)->mode[3] != 20 && ((*cmd)->c[0] == '\0'
		|| (if_only_i(ed_str(*cmd,
		NULL, (*fz)->nb[0] - giv_last(*fz)), ' '))) && (*fz)->cmd == NULL)
		return (1);
	return (0);
}

t_env	*treat_cmd(t_env *env, t_edit **cmd, t_his **hs, t_froz **fz)
{
	t_cmd	*ex;

	if (init_treatmt(&ex, cmd, fz))
		return (env);
	else if ((*fz)->mode[3] == 20 && ((*cmd)->c[0] == '\0' ||
		(if_only_i(ed_str(*cmd, NULL, (*fz)->nb[0] - giv_last(*fz)), ' '))))
	{
		add_his(hs, NULL, *fz);
		if (parsing(*cmd, *fz, &ex) == 1)
		{
			env = launchcmd(ex, env);
			init_free_his(hs, fz, 2, &ex);
		}
		else if ((*fz)->mode[3] == 0)
			init_free_his(hs, fz, 0, &ex);
	}
	else if (parsing(*cmd, *fz, &ex) == 1)
	{
		env = launchcmd(ex, env);
		init_free_his(hs, fz, 3, &ex);
	}
	else if ((*fz)->mode[3] == 0)
		init_free_his(hs, fz, 1, &ex);
	return (env);
}

void	add_his(t_his **hs, t_his *nw, t_froz *fz)
{
	if (!(fz->cmd && (nw = (t_his*)malloc(sizeof(t_his)))))
		return ;
	nw->cmd = ft_strdup(fz->cmd);
	while ((*hs)->prev != NULL)
		*hs = (*hs)->prev;
	if (if_only(nw->cmd, ' ') || ((*hs)->next->cmd && ft_strcmp(nw->cmd,
					(*hs)->next->cmd) == 0))
	{
		free(nw->cmd);
		free(nw);
		nw = NULL;
		return ;
	}
	(*hs)->next->prev = nw;
	nw->next = (*hs)->next;
	nw->prev = *hs;
	(*hs)->next = nw;
	*hs = (*hs)->next;
}

t_env	*exec_fct_re(t_cmd **ex, t_env *env, t_exec *s)
{
	char	**arr;

	arr = translate(env, ex);
	if (arr)
	{
		env = exec_fct(arr, env, ex, s);
		free_tab(arr);
	}
	*ex = (*ex)->next;
	return (env);
}

t_env	*launchcmd(t_cmd *ex, t_env *env)
{
	t_exec	s;

	init_launch(&s, &ex);
	while (ex->next != NULL)
	{
		if (pipe_on(ex))
			env = pipe_fct(&s, &ex, env);
		else if (ex->type == 4 && g_ok == 1)
			move_on(&ex, 4);
		else if (ex->type == 5 && g_ok == 0)
			move_on(&ex, 5);
		else if (ex->type == 0 && !(ex->next->type >= 6 &&
			ex->next->type <= 11))
			env = exec_fct_re(&ex, env, &s);
		else if (ex->type == 0 && ex->next->type >= 6 && ex->next->type <= 11)
			redirection_fork(&ex, &env, &s);
		else if (ex->type >= 6 && ex->type <= 11)
			redirection_no_cmd(&ex, &env, &s);
		else
			ex = ex->next;
	}
	return (env);
}
