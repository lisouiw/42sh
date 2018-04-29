/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paoroste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 23:35:20 by paoroste          #+#    #+#             */
/*   Updated: 2018/04/25 18:41:19 by paoroste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_comp42.h"

void				ft_left(t_data *list)
{
	if (list->cursor)
	{
		list->cursor = 0;
		while (list->next)
			list = list->next;
		list->cursor = 1;
	}
	else
		while (list)
		{
			if (list->next->cursor)
			{
				list->cursor = 1;
				list->next->cursor = 0;
				break ;
			}
			list = list->next;
		}
}

void				ft_right(t_data *list)
{
	t_data *tmp;

	tmp = list;
	while (list)
	{
		if (list->cursor)
		{
			list->cursor = 0;
			if (list->next == NULL)
			{
				tmp->cursor = 1;
				break ;
			}
			list->next->cursor = 1;
			break ;
		}
		list = list->next;
	}
}
