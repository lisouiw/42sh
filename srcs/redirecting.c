/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:54:10 by mallard           #+#    #+#             */
/*   Updated: 2018/05/04 03:47:17 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	redirection(t_cmd **ex, t_env **env, t_exec *s)
{
	char	**arr;

	arr = translate(*env, ex);
	*ex = (*ex)->next;
	if (arr && redirection_check_create(*ex, *env))
		redirecting_exec(ex, env, arr, s);
	else
	{
		g_ok = 1;
		exit(1);
	}
	free_tab(arr);
	while ((*ex)->type >= 6 && (*ex)->type <= 11)
		*ex = (*ex)->next;
}

void	redirection_fork(t_cmd **ex, t_env **env, t_exec *s)
{
	char	**arr;
	int		status;
	pid_t	pid;

	s->in = dup(0);
	s->out = dup(1);
	arr = translate(*env, ex);
	*ex = (*ex)->next;
	if ((pid = fork()) == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		if (arr && redirection_check_create(*ex, *env))
			redirecting_exec(ex, env, arr, s);
		else
			exit(1);
	}
	else
	{
		waitpid(-1, &status, 0);
		g_ok = WEXITSTATUS(status);
	}
	free_tab(arr);
	while ((*ex)->type >= 6 && (*ex)->type <= 11)
		*ex = (*ex)->next;
}

void	redirection_no_cmd(t_cmd **ex, t_env **env, t_exec *s)
{
	s->in = dup(0);
	s->out = dup(1);
	if (redirection_check_create(*ex, *env))
		redirecting_exec(ex, env, NULL, s);
	else
		g_ok = 1;
	dup2(s->out, 1);
	dup2(s->in, 0);
	while ((*ex)->type >= 6 && (*ex)->type <= 11)
		*ex = (*ex)->next;
}

char	**give_seven(t_cmd *ex, t_env *env)
{
	while (ex->next->type >= 6 && ex->next->type <= 11)
		ex = ex->next;
	while (ex->type >= 8 && ex->type <= 11)
		ex = ex->prev;
	if (ex->type == 6)
	{
		dup2(open("/tmp/in", O_RDONLY), 0);
		while ((ex->type >= 6 && ex->type <= 11) || ex->type == 0)
			ex = ex->next;
		return (NULL);
	}
	else if (ex->type != 7)
		return (NULL);
	return (translate(env, &ex));
}

void	redirecting_exec(t_cmd **ex, t_env **env, char **arr, t_exec *s)
{
	int		nw;
	char	**tmp;

	if ((tmp = give_seven(*ex, *env)) != NULL)
	{
		nw = (tmp[2] == NULL) ? open(tmp[1], O_RDWR) : open(tmp[2], O_RDONLY);
		dup2(nw, (tmp[2] == NULL ? 0 : ft_atoi(tmp[0])));
		free_tab(tmp);
	}
	if (arr != NULL)
	{
		wait(0);
		*env = exec_fct_nf(arr, *env, ex, s);
	}
}
