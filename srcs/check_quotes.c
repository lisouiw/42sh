/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 04:40:31 by ybensimo          #+#    #+#             */
/*   Updated: 2018/04/11 17:06:23 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

static char *get_var(char *str, char c, int *j)
{
	char    *var;
	int     i;
	int     safe;

	i = 0;
	if ((var = ft_memalloc(ft_strlen(str))) == NULL)
		exit(1);
	if (c == 0)
	{
		while (str[i] && str[i] != ' ' && str[i] != '\v' && str[i] != '\t')
		{
			var[i] = str[i];
			i++;
		}
		var[i] = '\0';
	}
	else
	{
		i++;
		safe = 0;
		if (str[i] && str[i] != c)
		{
			while (str[i] && str[i] != c)
			{
				var[safe++] = str[i];
				i++;
			}
			var[safe] = '\0';
		}

	}
	*j = i;
	return (var);
}

static int	insert(char *curline, int i)
{
	char	*tmp;
	int		a;

	if (!(tmp = ft_strnew(ft_strlen(curline))))
		return (-1);
	ft_bzero(tmp, ft_strlen(curline));
	a = 0;
	while (curline[i])
	{
		if (curline[i] == '{' || curline[i] == '[' || curline[i] == '(')
		{
			if (tmp[0] == '{')
			{
				free(tmp);
				return (-1);
			}
			tmp[a] = curline[i];
			a++;
		}
		if (curline[i] == '}' || curline[i] == ']' || curline[i] == ')')
		{
			a = (a == 0) ? a : a - 1;
			if (tmp[0] == '\0' || (curline[i] != tmp[a] + 1 && curline[i] != tmp[a] + 2))
			{
				free(tmp);
				return (-1);
			}
			tmp[a] = '\0';
		}
		i++;
	}
	if (tmp[0] != '\0')
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}

int		check_quote(char *cmd, char c, int i)
{
	int		j;

	j = i + 1;
	while (cmd[i] && cmd[i] != c)
		i++;
	if (!cmd[i])
	{
		ft_putstr_fd("42sh: lacking closing )\n", 2);
		return (-1);
	}
	if (insert(cmd, j) == -1)
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(cmd + j - 2, 2);
		ft_putstr_fd(": bad substitution\n", 2);
		return (-1);
	}
	return (i);
}

char	*find_variable(char *var, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	var = ft_strjoin(var, "=");
	while (tmp->next)
	{
		if (!ft_strcmp(var, tmp->name))
			return (tmp->ctn);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*charsub(char *var, char **cmd, int i, int j)
{
	char		*tmp;

	tmp = ft_strsub(*cmd, 0, i);
	tmp = ft_strjoin(tmp, var);
	tmp = ft_strjoin(tmp, ft_strsub(*cmd, j, ft_strlen(tmp) - j));
	return (tmp);
}

int		pls(t_env *env, char **cmd, int i, char c)
{
	int		k;
	char	*var;
	int		j;

	if (c != ' ')
	{
		i++;
		if ((k = check_quote(*cmd, c, i)) == -1)
			return (-1);
	}
	var = get_var(*cmd + i, c, &j);
	var = find_variable(var, env);
	if (!var)
	{
		ft_putstr_fd("42sh: bad substitution\n", 2);
		return (-1);
	}
	j = (c == ' ') ? j + i : j;
	*cmd = charsub(var, cmd, i, j);
	return (k);
}

int	loopy_loop(char **str, t_env *env)
{
	int		i;
	int		squote;
	int		dquote;
	int		j;
	t_op	*op;
	char	*var;
	char	*cmd;

	cmd = *str;
	i = 0;
	squote = 0;
	dquote = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			squote = (squote == 1) ? 0 : 1;
		else if (cmd[i] == '"')
			dquote = (dquote == 1) ? 0 : 1;
		if (cmd[i] == '$' && !squote)
		{
			if (cmd[i + 1] && cmd[i + 1] == '[')
			{
				if (check_quote(cmd, ']', i) == -1)
					return (-1);
				var = get_var(cmd + 1, ']', &j);
				op = calculator(var);
				if (op->priority != -1)
					charsub(ft_ltoa(op->x), &cmd, i, j);
			}
			else if (cmd[i + 1] && cmd[i + 1] == '{')
				j = pls(env, &cmd, i, '}');
			else if (cmd[i + 1] && cmd[i + 1] == '(')
				j = pls(env, &cmd, i, ')');
			else
				j = pls(env, &cmd, i , ' ');
			if (j == -1)
				return (-1);
			i = j;
		}
		else if (cmd[i] == '\\' && !squote)
		{
			if (cmd[i + 1])
				i++;
		}
		i++;
	}
	*str = cmd;
	return (i);
}
