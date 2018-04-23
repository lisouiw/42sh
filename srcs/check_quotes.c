/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:28:49 by mallard           #+#    #+#             */
/*   Updated: 2018/04/23 20:47:53 by mallard          ###   ########.fr       */
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

char	*charsub(char *var, char **cmd, int i, int j)
{
	char		*tmp;

	tmp = ft_strsub(*cmd, 0, i);
	tmp = ft_strjoin_free(tmp, var, 1);
	if (j != (int)ft_strlen(*cmd) - 1)
		tmp = ft_strjoin_free(tmp, ft_strsub(*cmd, j, ft_strlen(*cmd) - j), 3);
	free(*cmd);
	return (tmp);
}

char	*find_variable(char *var, t_env *env)
{
	t_env	*tmp;

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


int		pls(t_env *env, char **cmd, int i, char c)
{
	int		k;
	char	*var;
	int		j;

	k = 0;
	if (c != ' ')
	{
		if ((k = check_quote(*cmd, c, i)) == -1)
			return (-1);
		i++;
	}
	var = get_var(*cmd + i, c, &j);
	var = find_variable(var, env);
	if (!var)
	{
		ft_putstr_fd("42sh: bad substitution\n", 2);
		return (-1);
	}
	i = (c == ' ') ? i + 1 : i;
	j = (c == ' ') ? j + 1 : k;
	*cmd = charsub(var, cmd, i - 1, k + 1);
	return (k);
}

void	free_op(t_op **op)
{
	t_op	*tmp;
	t_op	*t;

	tmp = *op;
	while (tmp->next)
	{
		t = tmp;
		tmp = tmp->next;
		free(t);
		t = NULL;
	}
	free(tmp);
	tmp = NULL;
	*op = NULL;
}


int		expand_var_env(char **cmd, int i, t_env *env)
{
	char		*var;
	int			j;
	int			k;
	t_op		*op;
	char		*tmp;

	tmp = NULL;
	if ((*cmd)[i + 1] && (*cmd)[i + 1] == '[')
	{
		if ((k = check_quote(*cmd, ']', i)) == -1)
			return (-1);
		var = get_var(*cmd + i + 1, ']', &j);
		op = calculator(var);
		ft_strdel(&var);
		if (op && op->priority == -1)
		{
			free_op(&op);
			return (-1);
		}
		var = ft_ltoa(op->x);
		tmp = *cmd;
		*cmd = charsub(var, cmd, i, k + 1);
		free_op(&op);
		ft_strdel(&var);
	}
	else if ((*cmd)[i + 1] && (*cmd)[i + 1] == '{')
		j = pls(env, cmd, i, '}');
	else if ((*cmd)[i + 1] && (*cmd)[i + 1] == '(')
		j = pls(env, cmd, i, ')');
	else
		j = pls(env, cmd, i, ' ');
	return (j);
}

int	loopy_loop(char **str, t_env *env)
{
	int		i;
	int		squote;
	int		dquote;
	char	*cmd;
	int		size;

	cmd = *str;
	i = 0;
	squote = 0;
	dquote = 0;
	size = ft_strlen(cmd);
	while (i < size && cmd[i])
	{
		if (cmd[i] == '\'')
			squote = (squote == 1) ? 0 : 1;
		else if (cmd[i] == '"')
			dquote = (dquote == 1) ? 0 : 1;
		if (cmd[i] == '$' && !squote)
		{
			i = expand_var_env(&cmd, i, env);
			if (i == -1)
				return (-1);
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
