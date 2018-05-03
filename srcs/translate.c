/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:56:49 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:56:50 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

static void	check_b_2(int quote, char **arg, int i, int *j)
{
	if (quote == 0 && ft_strlen(arg[i]) > 1)
		ft_replace_b(arg[i], *j);
	else if (quote == 2)
	{
		if (arg[i][*j + 1] && ft_isvip(arg[i][*j + 1]))
			ft_replace_b(arg[i], *j);
	}
	else
		*j = *j + 1;
}

void		check_b(char **arg)
{
	int		i;
	int		j;
	int		quote;
	char	*tmp;

	i = -1;
	while (arg[++i])
	{
		quote = 0;
		j = -1;
		if (arg[i][0] == '"' || arg[i][0] == '\'')
			quote = (arg[i][0] == '\'') ? 1 : 2;
		while (arg[i][++j])
		{
			tmp = arg[i];
			if (arg[i][j] == 92)
				check_b_2(quote, arg, i, &j);
		}
		if (quote)
		{
			ft_replace_b(arg[i], 0);
			j = (j > 2) ? j - 2 : j - 1;
			arg[i][j] = '\0';
		}
	}
}

static void	charcut_2(char *cmd, int *i, int *k, char **arg)
{
	int		j;
	char	c;

	if (cmd[*i] != ' ' && !ft_isquote(cmd[*i]))
	{
		if (cmd[*i] == 92)
			if (cmd[*i + 1] == '"' || cmd[*i + 1] == '\'')
				*i = *i + 1;
		j = ft_strchr_quote(cmd + *i, ' ');
		arg[*k] = ft_strsub(cmd, *i, j);
		*k = *k + 1;
		*i = *i + j - 1;
	}
	else if ((c = cmd[*i]) && (c == '"' || c == '\''))
	{
		j = ft_strchr_quote(cmd + *i + 1, c);
		if (j == 0)
			arg[*k] = ft_memalloc(2);
		else
			arg[*k] = ft_strsub(cmd, *i, j + 2);
		*k = *k + 1;
		*i = *i + j + 1;
	}
}

char		**charcut(char *cmd)
{
	char	**arg;
	int		i;
	int		k;
	int		size;

	i = -1;
	k = arg_nbr(cmd);
	if (!(arg = (char **)malloc(sizeof(char *) * (k + 1))))
		exit(1);
	k = 0;
	size = ft_strlen(cmd);
	while (i < size && cmd[++i])
		charcut_2(cmd, &i, &k, arg);
	arg[k] = NULL;
	check_b(arg);
	return (arg);
}

char		**translate(t_env *env, t_cmd **ex)
{
	char	*cmd;

	cmd = (*ex)->cmd;
	if (loopy_loop(&cmd, env) == -1)
		return (NULL);
	(*ex)->cmd = cmd;
	(*ex)->cmd = glob_parsing(ex);
	cmd = (*ex)->cmd;
	return (charcut(cmd));
}
