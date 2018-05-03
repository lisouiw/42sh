/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_tool_comp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:43:39 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:43:45 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_comp42.h"

t_data			*hey_hook(int buf, t_data *list, t_stop *stop)
{
	if (buf == DOWN || buf == UP || buf == RIGHT || buf == LEFT || buf == ENTER
			|| buf == TAB)
	{
		if (buf == DOWN && list->how_row > 1)
			ft_down(list, list->how_col, list->how_prop, 0);
		if (buf == UP && list->how_row > 1)
			ft_up(list, list->how_col, list->how_prop, 0);
		if (buf == RIGHT || buf == TAB)
			ft_right(list);
		if (buf == LEFT)
			ft_left(list);
		if (buf == ENTER)
			final_print(list, stop);
		return (list);
	}
	else
	{
		free_data(list);
		free_stop(stop);
		out_clean();
		tputs(tgetstr("up", NULL), 0, ft_put);
		tputs(tgetstr("sc", NULL), 0, ft_put);
		return (NULL);
	}
	return (list);
}

int				out_size(t_data *list)
{
	size_t				y;
	size_t				x;
	struct winsize		size;

	y = 1;
	x = list->max_len;
	ioctl(0, TIOCGWINSZ, &size);
	list->how_col = size.ws_col / (list->max_len + 1);
	((list->max_len * list->how_col) + (list->how_col * 1)) < size.ws_col ?
		list->how_col : list->how_col--;
	if (list->how_col > 0)
	{
		if (list->how_prop % list->how_col != 0)
			list->how_row = (list->how_prop / list->how_col) + 1;
		else
			list->how_row = list->how_prop / list->how_col;
	}
	if ((size.ws_row < (list->how_row + 3)) || (list->max_len > size.ws_col))
	{
		list = NULL;
		return (0);
	}
	return (1);
}

t_data			*check_command(t_data *list, t_stop *stop)
{
	int			buf;

	buf = 0;
	if (read(0, &buf, sizeof(int)) && out_size(list))
	{
		list = hey_hook(buf, list, stop);
		if (list == NULL)
			return (NULL);
		print_list(list, 0, 0);
	}
	return (list);
}

void			ft_comp42(int nb, char *str, t_stop *list)
{
	if (nb == 1)
	{
		free(list->print);
		list->print = strdup(str);
		free(str);
		list->stop = 1;
	}
	else if (nb == 3)
	{
		free(list->print);
		list->print = strdup(str);
		free(str);
	}
}

void			final_print(t_data *list, t_stop *stop)
{
	while (list)
	{
		if (list->cursor)
			ft_comp42(1, epur_str(list->arg), stop);
		list = list->next;
	}
}
