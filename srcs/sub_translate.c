/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:35:02 by mallard           #+#    #+#             */
/*   Updated: 2018/04/28 17:39:22 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

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

static void	arg_nbr2(char *cmd, int *arg, int *i, char c)
{
	int		active;

	*i = *i + 1;
	if (cmd[*i] == c)
		arg++;
	while (cmd[*i] && cmd[*i] != c)
	{
		if (active == 0)
		{
			active = 1;
			arg++;
		}
		*i = *i + 1;
	}
	active = 0;
}

int			arg_nbr(char *cmd)
{
	int		i;
	int		arg;
	int		active;
	int		size;
	char	c;

	size = (int)ft_strlen(cmd);
	i = -1;
	arg = 0;
	active = 0;
	while (i < size && cmd[++i])
	{
		if (cmd[i] != ' ' && !ft_isquote(cmd[i]) && !(active = 0))
			while (cmd[i] && cmd[i++] != ' ')
			{
				if (active == 0)
				{
					active = 1;
					arg++;
				}
			}
		else if ((c = cmd[i]) && (c == '"' || c == '\''))
			arg_nbr2(cmd, &arg, &i, c);
	}
	return (arg);
}
