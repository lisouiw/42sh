/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_check_quotes_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:55:22 by mallard           #+#    #+#             */
/*   Updated: 2018/05/04 02:36:38 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

static int		insert_2(char *tmp, int a)
{
	a = (tmp[0] != '\0' || a == -1) ? -1 : 0;
	ft_strdel(&tmp);
	return (a);
}

static int		insert(char *curline, int i, int a)
{
	char		*tmp;

	if (!(tmp = ft_strnew(ft_strlen(curline))))
		return (-1);
	ft_bzero(tmp, ft_strlen(curline));
	while (curline[i])
	{
		if (curline[i] == '{' || curline[i] == '[' || curline[i] == '(')
		{
			if (tmp[0] == '{' && (a = -1))
				break ;
			tmp[a++] = curline[i];
		}
		if (curline[i] == '}' || curline[i] == ']' || curline[i] == ')')
		{
			a = (a == 0) ? a : a - 1;
			if ((tmp[0] == '\0' || (curline[i] != tmp[a] + 1 && \
							curline[i] != tmp[a] + 2)) && (a = -1))
				break ;
			tmp[a] = '\0';
		}
		i++;
	}
	a = insert_2(tmp, a);
	return (a);
}

int				check_quote(char *cmd, char c, int i)
{
	int			j;

	j = i + 1;
	while (cmd[i] && cmd[i] != c)
		i++;
	if (!cmd[i])
	{
		ft_putstr_fd("42sh: lacking closing )\n", 2);
		g_ok = 1;
		return (-1);
	}
	if (insert(cmd, j, 0) == -1)
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(cmd + j - 1, 2);
		ft_putstr_fd(": bad substitution\n", 2);
		g_ok = 1;
		return (-1);
	}
	return (i);
}

char			*charsub(char *var, char **cmd, int i, int j)
{
	char		*tmp;

	tmp = ft_strsub(*cmd, 0, i);
	if (var)
		tmp = ft_strjoin_free(tmp, var, 1);
	if ((*cmd)[i] == '~')
		i++;
	tmp = ft_strjoin_free(tmp, ft_strsub(*cmd, i, ft_strlen(*cmd) - j), 3);
	free(*cmd);
	return (tmp);
}

char			*find_variable(char *var, t_env *env)
{
	t_env		*tmp;

	tmp = env;
	var = ft_strjoin_free(var, "=", 1);
	while (tmp->next)
	{
		if (!ft_strcmp(var, tmp->name))
		{
			ft_strdel(&var);
			return (tmp->ctn);
		}
		tmp = tmp->next;
	}
	ft_strdel(&var);
	return (NULL);
}
