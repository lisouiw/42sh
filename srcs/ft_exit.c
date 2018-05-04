/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:48:39 by mallard           #+#    #+#             */
/*   Updated: 2018/05/04 03:45:01 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	ft_exit(char *cmd)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	if (ft_strlen(cmd) > 4)
		exit(42);
	while (cmd && cmd[i])
	{
		if (cmd[i] < '0' || cmd[i] > '9')
			a = 42;
		i++;
	}
	if (a == 42)
	{
		free(cmd);
		exit(255);
	}
	else
		a = ft_atoi(cmd);
	free(cmd);
	if (a >= 0 && a <= 255)
		exit(a);
	exit(42);
}

void	build_exit(char **cut, t_env *env, t_cmd **ex)
{
	char	*cmd;

	cmd = NULL;
	if (cut[0] && cut[1] && cut[2])
	{
		ft_putstr_fd("42sh: exit: too many arguments\n", 2);
		g_ok = 1;
	}
	else
	{
		if (cut[1])
			cmd = ft_strdup(cut[1]);
		free_tab(cut);
		free_list(&env);
		free_all_ex(ex);
		free_for_exit(cmd, 0);
	}
}
