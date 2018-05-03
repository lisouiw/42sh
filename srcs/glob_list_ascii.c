/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_list_ascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:51:19 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:51:21 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

t_glob	*glob_ascii(t_glob *g)
{
	t_glob	*tmp;
	char	*s;

	tmp = g;
	while (tmp->next != NULL)
	{
		if (ft_strcmp(tmp->cmd, tmp->next->cmd) > 0)
		{
			s = tmp->cmd;
			tmp->cmd = tmp->next->cmd;
			tmp->next->cmd = s;
			tmp = g;
		}
		else
			tmp = tmp->next;
	}
	return (g);
}
