/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_backslash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:53:12 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:53:13 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int			last_multiple_char(char *s, char c)
{
	int		i;
	int		a;

	i = ft_strlen(s);
	a = i;
	if (s[i - 1] == 92)
	{
		while (s[--i] && s[i] == c)
			;
		if ((a - i + 1) % 2 == 1)
			return (1);
	}
	return (0);
}

int			parse_synthaxe_back(t_cmd *ex)
{
	char	*s;

	while (ex->next != NULL)
		ex = ex->next;
	ex = ex->prev;
	s = ex->cmd;
	if (last_multiple_char(s, 92))
		return (1);
	return (0);
}
