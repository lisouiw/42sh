/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:56:29 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:56:32 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

char	*strjoin_free(char *nw, char *sub, int i)
{
	char	*tmp;

	if (nw && sub == NULL)
		sub = nw;
	else if (nw && sub)
	{
		tmp = ft_strjoin(sub, nw);
		if (i == 1 || i == 3)
		{
			free(nw);
			nw = NULL;
		}
		if (i == 2 || i == 3)
		{
			free(sub);
			sub = NULL;
		}
		return (tmp);
	}
	return (sub);
}

char	*strjoin_free_n(char *nw, char *sub, int i)
{
	char	*tmp;

	if (nw && sub == NULL)
		sub = nw;
	else if (nw && sub)
	{
		tmp = ft_strjoin(nw, sub);
		if (i == 1 || i == 3)
			free(nw);
		if (i == 2 || i == 3)
			free(sub);
		return (tmp);
	}
	return (sub);
}

void	move_on(t_cmd **ex, int i)
{
	*ex = (*ex)->next;
	if (i == 4)
		while ((*ex)->type != 5 && (*ex)->type != 13 && (*ex)->type != 42)
			*ex = (*ex)->next;
	else if (i == 5)
		while ((*ex)->type != 4 && (*ex)->type != 13 && (*ex)->type != 42)
			*ex = (*ex)->next;
}
