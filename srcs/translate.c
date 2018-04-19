/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 13:54:02 by mallard           #+#    #+#             */
/*   Updated: 2018/04/19 17:57:43 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		ft_isquote(char c)
{
	return ((c == '"' || c == '\'' || c == '\\') ? 1 : 0);
}

int		arg_nbr(char *cmd)
{
	int		i;
	int		arg;
	int		active;
	int		size = (int)ft_strlen(cmd);
	char	c;

	i = -1;
	arg = 0;
	active = 0;
	while (cmd[++i] && i < size)
	{
		if (cmd[i] != ' ' && !ft_isquote(cmd[i]))
		{
			while (cmd[i] && cmd[i] != ' ')
			{
				if (active == 0)
				{
					active = 1;
					arg++;
				}
				i++;
			}
			active = 0;
		}
		else if ((c = cmd[i]) && (c == '"' || c == '\''))
		{
			i++;
			while (cmd[i] && cmd[i] != c)
			{
				if (active == 0)
				{
					active = 1;
					arg++;
				}
				++i;
			}
			active = 0;

		}
	}
	return (arg);
}

char		**charcut(char *cmd)
{
	char	**arg;
	int		i;
	int		k;
	int		j;
	int     size = (int)ft_strlen(cmd);
	char	c;

	i = -1;
	k = arg_nbr(cmd);
	if (!(arg = (char **)malloc(sizeof(char *) * (k + 1))))
		exit(1);
	arg[k] = NULL;
	k = 0;
	while (cmd[++i] && i < size)
	{
		if (cmd[i] == '\\')
			i++;
		else if (cmd[i] != ' ' && !ft_isquote(cmd[i]))
		{
			j 	= ft_strchr_quote(cmd + i, ' ');
			if (j == 0)
				break;
			arg[k++] = ft_strsub(cmd, i, j);
			i = i + j - 1;
		}
		else if ((c = cmd[i]) && (c == '"' || c == '\''))
		{
			j = ft_strchr_quote(cmd + i + 1, c);
			if (j == 0)
				break;
			arg[k++] = ft_strsub(cmd, i + 1, j);
			i = i + j + 1;
		}
	}
	return (arg);
}

char		**translate(t_env *env, char *cmd)
{
	if (loopy_loop(&cmd, env) == -1)
		return (NULL);
	return (charcut(cmd));
}
