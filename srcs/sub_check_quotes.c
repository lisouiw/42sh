/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 15:28:49 by mallard           #+#    #+#             */
/*   Updated: 2018/04/30 19:06:48 by mallard          ###   ########.fr       */
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

static void		loop_2(char *cmd, int *i, int *squote, int *dquote)
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
	*i = j;
}

void			ft_home(char **cmd, int i, t_env *env)
{
	char		*tmp;

	tmp = find_variable(ft_strdup("HOME"), env);
	if (tmp)
		*cmd = charsub(tmp, cmd, i, 0);
}

int				loopy_loop(char **str, t_env *env)
{
	int			i;
	int			squote;
	int			dquote;
	char		*cmd;
	int			size;

	cmd = *str;
	i = 0;
	squote = 0;
	dquote = 0;
	size = ft_strlen(cmd);
	while (i < size && cmd[i])
	{
		printf("i = %d\n", i);
		loop_2(cmd, &i, &squote, &dquote);
		printf("i2 = %d\n", i);
		if (cmd[i] == '$' && !squote)
		{
			i = expand_var_env(&cmd, i, env);
			if (i == -1)
				return (-1);
		}
		else if (cmd[i] == '~')
			ft_home(&cmd, i, env);
		i++;
	}
	*str = cmd;
	return (i);
}
