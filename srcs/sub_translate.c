/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:56:04 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:56:08 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void		ft_home(char **cmd, int i, t_env *env)
{
	char	*tmp;

	if ((*cmd)[i + 1] != '/')
		tmp = "/Users/";
	else
		tmp = find_variable(ft_strdup("HOME"), env);
	if (tmp)
		*cmd = charsub(tmp, cmd, i, 0);
}

void		ft_replace_b(char *str, int i)
{
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i + 1] = '\0';
}

int			ft_isquote(char c)
{
	return ((c == '"' || c == '\'') ? 1 : 0);
}

static void	arg_nbr2(char *cmd, int *i, char c)
{
	int		active;

	*i = *i + 1;
	while (cmd[*i] && cmd[*i] != c)
	{
		if (active == 0)
		{
			active = 1;
		}
		*i = *i + 1;
	}
	active = 0;
}

int			arg_nbr(char *cmd)
{
	int		i;
	int		arg;
	int		size;
	char	c;

	size = (int)ft_strlen(cmd);
	i = -1;
	arg = 0;
	while (i < size && cmd[++i])
	{
		if (cmd[i] != ' ' && !ft_isquote(cmd[i]))
		{
			if (cmd[i] == 92)
				if (cmd[i + 1] == '"' || cmd[i + 1] == '\'')
					i++;
			i = i + ft_strchr_quote(cmd + i, ' ');
			arg++;
		}
		else if ((c = cmd[i]) && (c == '"' || c == '\'') && ++arg)
			arg_nbr2(cmd, &i, c);
	}
	return (arg);
}
