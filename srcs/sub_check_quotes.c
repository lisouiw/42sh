/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_check_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:55:10 by mallard           #+#    #+#             */
/*   Updated: 2018/05/04 00:52:58 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

char			*get_var(char *str, char c, int *j, int i)
{
	char		*var;
	int			safe;

	if ((var = ft_memalloc(ft_strlen(str))) == NULL)
		exit(1);
	if (c == ' ')
	{
		while (str[i] && !ft_var_end(str[i++]))
			var[i - 1] = str[i - 1];
		var[i] = '\0';
	}
	else
	{
		safe = 0;
		if (str[++i] && str[i] != c)
		{
			while (str[i] && str[i] != c)
				var[safe++] = str[i++];
			var[safe] = '\0';
		}
	}
	*j = i;
	return (var);
}

static int		expand_var_env_2(char **cmd, int i, t_env *env)
{
	int			j;

	if ((*cmd)[i + 1] && (*cmd)[i + 1] == '{')
		j = trad_d(env, cmd, i, '}');
	else if ((*cmd)[i + 1] && (*cmd)[i + 1] == '(')
		j = trad_d(env, cmd, i, ')');
	else
		j = trad_d(env, cmd, i, ' ');
	return (j);
}

int				expand_var_env(char **cmd, int i, t_env *env)
{
	char		*var;
	int			j;
	int			k;
	t_op		*op;

	if ((*cmd)[i + 1] && (*cmd)[i + 1] == '[')
	{
		if ((k = check_quote(*cmd, ']', i)) == -1)
			return (-1);
		var = get_var(*cmd + i + 1, ']', &j, 0);
		op = calculator(var);
		ft_strdel(&var);
		if (op && op->priority == -1)
		{
			free_op(&op);
			return (-1);
		}
		var = ft_ltoa(op->x);
		*cmd = charsub(var, cmd, i, k + 1);
		free_op(&op);
		ft_strdel(&var);
	}
	else
		j = expand_var_env_2(cmd, i, env);
	return (j);
}

static int		loop_2(char *cmd, int *i, int *squote, int *dquote)
{
	int			j;

	j = *i;
	if (cmd[j] == '\\')
		j++;
	if (cmd[j] == '\'')
		*squote = (*squote == 1) ? 0 : 1;
	else if (cmd[j] == '"')
		*dquote = (*dquote == 1) ? 0 : 1;
	if (cmd[j] == '\\' && *squote == 0)
	{
		if (cmd[j + 1])
			j++;
		if (*dquote == 0)
			if (cmd[j] != '\\')
				j--;
	}
	if (j == *i)
		return (0);
	*i = j;
	return (1);
}

int				loopy_loop(char **str, t_env *env)
{
	int			i;
	int			squote;
	int			dquote;
	char		*cmd;
	int			size;

	cmd = *str;
	i = -1;
	squote = 0;
	dquote = 0;
	size = ft_strlen(cmd);
	while (i < size && cmd[++i])
		if (!loop_2(cmd, &i, &squote, &dquote))
		{
			if (cmd[i] == '$' && !squote)
			{
				i = expand_var_env(&cmd, i, env);
				if (i == -1)
					return (-1);
			}
			else if (cmd[i] == '~' && !squote)
				ft_home(&cmd, i, env);
		}
	*str = cmd;
	return (i);
}
