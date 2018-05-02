/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paoroste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 04:54:51 by paoroste          #+#    #+#             */
/*   Updated: 2018/05/02 13:42:55 by paoroste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_comp42.h"

static void		do_up(t_data *list, int col, int prop, int i)
{
	int			end;
	int			nb;

	nb = i;
	end = 0;
	while (nb + col <= prop)
	{
		nb = nb + col;
		end++;
	}
	end = (end * col) + i;
	while (i < end)
	{
		list = list->next;
		i++;
	}
	list->cursor = 1;
}

void			ft_up(t_data *list, int col, int prop, int i)
{
	int			nb;

	while (list)
	{
		if (list->cursor)
		{
			list->cursor = 0;
			nb = i;
			if (i - col >= 0)
			{
				while (nb != i - col)
				{
					list = list->prev;
					nb--;
				}
				list->cursor = 1;
			}
			else
				do_up(list, col, prop, i);
			break ;
		}
		list = list->next;
		i++;
	}
}

static void		do_down(t_data *list, int col, int prop, int i)
{
	int			begin;
	int			nb;

	prop = prop + 0;
	nb = i;
	begin = 0;
	while (nb - col >= 0)
	{
		nb = nb - col;
		begin++;
	}
	begin = begin * col;
	while (begin > 0)
	{
		list = list->prev;
		begin--;
	}
	list->cursor = 1;
}

void			ft_down(t_data *list, int col, int prop, int i)
{
	int			nb;

	while (list)
	{
		if (list->cursor)
		{
			list->cursor = 0;
			nb = i;
			if (i + col <= prop)
			{
				while (nb != i + col)
				{
					list = list->next;
					nb++;
				}
				list->cursor = 1;
			}
			else
				do_down(list, col, prop, i);
			break ;
		}
		list = list->next;
		i++;
	}
}
