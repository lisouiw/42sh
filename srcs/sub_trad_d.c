/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_trad_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:55:52 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:55:54 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int				trad_d(t_env *env, char **cmd, int i, char c)
{
	int			k;
	char		*var;
	int			j;

	k = 0;
	if (c != ' ')
	{
		if ((k = check_quote(*cmd, c, i)) == -1)
			return (-1);
		i++;
	}
	if ((*cmd)[i] == '$')
		i++;
	var = get_var(*cmd + i, c, &j, 0);
	var = find_variable(var, env);
	j = (c == ' ') ? i + j : k + 1;
	*cmd = charsub(var, cmd, i - 1, j);
	return (k);
}

int				ft_var_end(char c)
{
	return (c == ' ' && c == '\v' && c == '\t' && c == '"' \
			&& c == '\\' && c == '\'') ? 1 : 0;
}
