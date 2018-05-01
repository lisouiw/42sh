/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paoroste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 23:35:20 by paoroste          #+#    #+#             */
/*   Updated: 2018/05/01 14:08:47 by paoroste         ###   ########.fr       */
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

void				s_winch(int i)
{
	(void)i;
	if (out_size(g_se))
	{
		tputs(tgetstr("cl", NULL), 0, ft_put);
		print_list(g_se, 0, 0);
	}
	else
		g_se2->stop = 2;
}

void				ft_move(void)
{
	signal(SIGWINCH, s_winch);
}

char				*get_path2(t_comp *data, int i, int path, int *tabi)
{
	char	*new;

	while (data->cmd[0][i])
	{
		if (data->cmd[0][i] == '/')
			path = 1;
		if (data->cmd[0][i + 1] == '\0' && (data->cmd[0][i] == '/'))
			data->all_prop = 1;
		i++;
	}
	free(data->find);
	data->find = find(data->cmd[0], tabi, NULL, NULL);
	free(data->path);
	if (path == 1)
		new = cut_path(data->cmd[0]);
	else
		new = strdup("./");
	return (new);
}
/*signal(SIGWINCH, s_winch);
  if (stop->stop == 2)
  {
  free_stop(stop);
//ft_comp42(3, strdup(list->arg), stop);
free_data(list);
out_clean();
tputs(tgetstr("up", NULL), 0, ft_put);
tputs(tgetstr("sc", NULL), 0, ft_put);
return (NULL);
}*/
