/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:42:44 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:42:48 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_comp42.h"

void		free_data(t_data *list)
{
	t_data	*tmp;

	while (list)
	{
		free(list->arg);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void		free_comp(t_comp *data)
{
	free(data->path);
	free_tab(data->cmd);
	free_tab(data->in_path);
	free(data->str);
	free(data->d_name);
	free(data->find);
	free(data);
}

void		stop_init(t_stop *stop, char *str, int i)
{
	stop->nb = where_am_i(str, i);
	stop->print = ft_strdup("");
	stop->cut = 0;
	stop->sig = 0;
	stop->stop = 0;
	stop->add = 0;
}

char		*epur_str(char *str)
{
	int		i;
	int		nb;
	char	*new;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (!IS_SPACE(str[i]))
			nb++;
		i++;
	}
	new = (char*)malloc(sizeof(char) * (nb + 1));
	nb = 0;
	i = 0;
	while (str[i])
	{
		if (!IS_SPACE(str[i]))
			new[nb++] = str[i];
		i++;
	}
	new[nb] = '\0';
	return (new);
}

int			do_space(char *command)
{
	int			i;
	int			space;

	i = 0;
	space = 0;
	if (command[0] == '\0')
		return (1);
	while ((command[i]))
	{
		if (!IS_SPACE(command[i]))
			space = 1;
		if ((command[i + 1] == '\0' && space != 1))
			return (1);
		i++;
	}
	return (0);
}
