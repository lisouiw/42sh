/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paoroste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 23:35:20 by paoroste          #+#    #+#             */
/*   Updated: 2018/05/04 03:01:01 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_comp42.h"

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
	g_se2->sig = 2;
}

t_stop				*ft_set_mssg(t_data *list)
{
	if (list == NULL)
		tputs(tgetstr("bl", NULL), 1, ft_put);
	else if (list->how_prop > 175)
		tputs(tgetstr("vb", NULL), 1, ft_put);
	if (list != NULL)
		free_data(list);
	return (NULL);
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
