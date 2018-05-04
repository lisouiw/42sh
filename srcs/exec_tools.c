/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:45:16 by mallard           #+#    #+#             */
/*   Updated: 2018/05/04 03:58:18 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

t_env	*exec_fct_nf_build(char **cut, t_env *env, t_exec *s)
{
	if (ft_strcmp("echo", cut[0]) == 0)
		print_tab(cut, 0);
	else if (ft_strcmp("env", cut[0]) == 0)
		builtin_env(cut, env, s);
	else if (ft_strcmp("setenv", cut[0]) == 0)
		b_setenv(cut, env);
	else if (env && ft_strcmp("unsetenv", cut[0]) == 0)
		b_unset(cut, &env, 0);
	else if (ft_strcmp("cd", cut[0]) == 0)
		b_cd(&cut[1], &env, 0);
	exit(g_ok);
	return (env);
}

t_env	*exec_fct_build(char **cut, t_env *env, t_exec *s)
{
	if (ft_strcmp("echo", cut[0]) == 0)
		print_tab(cut, 0);
	else if (ft_strcmp("env", cut[0]) == 0)
		builtin_env(cut, env, s);
	else if (ft_strcmp("setenv", cut[0]) == 0)
		b_setenv(cut, env);
	else if (env && ft_strcmp("unsetenv", cut[0]) == 0)
		b_unset(cut, &env, 0);
	else if (ft_strcmp("cd", cut[0]) == 0)
		b_cd(&cut[1], &env, 0);
	return (env);
}

int		give_path(t_env *env, char **cut, int i, char **tab_env)
{
	char	**path;
	char	*cmd;
	pid_t	father;
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
				if ((father = fork()) < 0)
					exit(1);
				if (wait(NULL) && father == 0)
					execve(cmd, cut, tab_env);
			}
			free(cmd);
		}
		free_tab(path);
	}
	return (a);
}

char	**list_to_tab(t_env *env, char **tab_env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		++i;
	}
	if (!(tab_env = (char**)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (env != NULL)
	{
		tab_env[i++] = ft_strjoin(env->name, env->ctn);
		env = env->next;
	}
	tab_env[i] = NULL;
	return (tab_env);
}
