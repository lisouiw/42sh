/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paoroste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 18:30:18 by paoroste          #+#    #+#             */
/*   Updated: 2018/04/27 18:08:31 by paoroste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_comp42.h"

void			print_list(t_data *list, int x, int y)
{
	int	row;
	int	col;

	row = list->how_row;
	col = list->how_col;
	tputs(tgetstr("rc", NULL), 1, ft_put);
	tputs(tgetstr("cd", NULL), 1, ft_put);
	tputs(tgetstr("sc", NULL), 1, ft_put);
	while (y < row)
	{
		while (x < col && list)
		{
			if (list->cursor)
				tputs(tgetstr("mr", NULL), 1, ft_put);
			ft_putstr_fd(list->arg, 0);
			if (list->next)
				ft_putstr_fd(" ", 0);
			tputs(tgetstr("me", NULL), 1, ft_put);
			list = list->next;
			x++;
		}
		x = 0;
		ft_putstr_fd("\n", 0);
		y++;
	}
}

void			out_clean(void)
{
	tputs(tgetstr("rc", NULL), 1, ft_put);
	tputs(tgetstr("cd", NULL), 1, ft_put);
	tputs(tgetstr("ve", NULL), 1, ft_put);
}

t_data			*get_args(char **av, int i, int nb, t_data *list)
{
	t_data		*tmp;

	if (av == NULL)
		return (NULL);
	list = (t_data*)malloc(sizeof(t_data));
	list->max_len = nb;
	list->arg = strdupmore(av[0], nb);
	list->cursor = 1;
	list->next = NULL;
	list->prev = NULL;
	tmp = list;
	while (av[i])
	{
		tmp->next = (t_data*)malloc(sizeof(t_data));
		tmp = tmp->next;
		tmp->cursor = 0;
		tmp->arg = strdupmore(av[i], nb);
		tmp->next = NULL;
		tmp->prev = do_prev(list, tmp);
		i++;
	}
	free_tab(av);
	list->how_prop = i - 1;
	return (list);
}

t_stop			*core2_comp42(t_data *list, t_stop *stop)
{
	print_list(list, 0, 0);
	while (1)
	{
		g_se = list;
		if ((list = check_command(list, stop)) == NULL)
			return (NULL);
		(stop->stop == 1) ? out_clean() : 0;
		if (stop->stop == 1)
		{
			free_data(list);
			return (stop);
		}
	}
}

t_stop			*core_comp42(char *str, t_data *list, t_stop *stop, int *tabi)
{
	list = get_prop((str), stop, list, tabi);
	(list != NULL) ? out_size(list) : 0;
	if (list != NULL && list->how_prop <= 175 && out_size(list))
		ft_set_term(1, list->how_row);
	else
		free_data(list);
	if (list == NULL || list->how_prop > 175 || (!(out_size(list))))
	{
		free_stop(stop);
		return (NULL);
	}
	else if (out_size(list) && list->how_prop >= 1)
		return (core2_comp42(list, stop));
	else
	{
		out_clean();
		(list->how_prop == 0) ? ft_comp42(3, strdup(list->arg), stop) : 0;
		free_data(list);
		return (stop);
	}
}
