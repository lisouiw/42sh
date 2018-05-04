/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:45:10 by mallard           #+#    #+#             */
/*   Updated: 2018/05/04 03:56:37 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

t_env	*exec_fct_nf(char **cut, t_env *env, t_cmd **ex, t_exec *s)
{
	if (ft_strcmp("echo", cut[0]) == 0 || ft_strcmp("env", cut[0]) == 0 ||
		ft_strcmp("setenv", cut[0]) == 0 ||
			(env && ft_strcmp("unsetenv", cut[0]) == 0)
				|| ft_strcmp("cd", cut[0]) == 0)
		env = exec_fct_nf_build(cut, env, s);
	else if (ft_strcmp(cut[0], "exit") == 0)
		build_exit(cut, env, ex);
	else
		b_other_nf(cut, env, s);
	return (env);
}

t_env	*exec_fct(char **cut, t_env *env, t_cmd **ex, t_exec *s)
{
	char	*cmd;

	cmd = NULL;
	if (ft_strcmp("echo", cut[0]) == 0 || ft_strcmp("env", cut[0]) == 0 ||
	ft_strcmp("setenv", cut[0]) == 0 ||
		(env && ft_strcmp("unsetenv", cut[0]) == 0)
			|| ft_strcmp("cd", cut[0]) == 0)
		env = exec_fct_build(cut, env, s);
	else if (ft_strcmp(cut[0], "exit") == 0)
		build_exit(cut, env, ex);
	else
		b_other(cut, env);
	return (env);
}

void	b_other(char **cut, t_env *env)
{
	char	**tab_env;
	pid_t	pid;
	int		status;

	if ((tab_env = list_to_tab(env, NULL)))
	{
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0 && wait(0) && execve(cut[0], cut, tab_env) == -1)
		{
			if (wait(0) && give_path_nf(env, cut, -1, tab_env) == -1)
			{
				ft_putstr_fd("sh: command not found: ", 2);
				ft_putendl_fd(cut[0], 2);
				g_ok = 1;
				exit(1);
			}
		}
		else
		{
			waitpid(-1, &status, 0);
			g_ok = WEXITSTATUS(status);
		}
	}
	free_tab(tab_env);
}

void	b_other_nf(char **cut, t_env *env, t_exec *s)
{
	char	**tab_env;

	if (s)
		;
	if ((tab_env = list_to_tab(env, NULL)))
	{
		if (wait(0) && execve(cut[0], cut, tab_env) == -1)
			if (give_path_nf(env, cut, -1, tab_env) == -1)
			{
				ft_putstr_fd("sh: command not found: ", 2);
				ft_putendl_fd(cut[0], 2);
				exit(1);
			}
	}
	free_tab(tab_env);
}

int		give_path_nf(t_env *env, char **cut, int i, char **tab_env)
{
	char	**path;
	char	*cmd;
	int		a;

	a = -1;
	while (env && env->next != NULL && ft_strcmp("PATH=", env->name) != 0)
		env = env->next;
	if (env && ft_strcmp("PATH=", env->name) == 0 &&
			(path = ft_strsplit(env->ctn, ':')))
	{
		while (path[++i] && a == -1 && (cmd = t_strjoin(path[i], "/", cut[0])))
		{
			if ((a = access(cmd, F_OK)) == 0)
			{
				if (wait(0))
					a = execve(cmd, cut, tab_env);
			}
			free(cmd);
		}
		free_tab(path);
	}
	return (a);
}
