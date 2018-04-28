/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_list_ascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:02:09 by ltran             #+#    #+#             */
/*   Updated: 2018/04/26 18:12:47 by ltran            ###   ########.fr       */
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
