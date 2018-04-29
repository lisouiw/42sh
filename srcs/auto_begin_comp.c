/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paoroste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:35:57 by paoroste          #+#    #+#             */
/*   Updated: 2018/04/30 01:31:48 by paoroste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_comp42.h"

void			ft_set_term(int i, int nb)
{
	if ((tputs(tgetstr("sf", NULL), 1, ft_put) == ERR))
		return ;
	if ((tputs(tgetstr("sf", NULL), 1, ft_put) == ERR))
		return ;
	while (i <= nb)
	{
		if ((tputs(tgetstr("sf", NULL), 1, ft_put) == ERR))
			return ;
		i++;
	}
	i = 0;
	while (i <= nb)
	{
		if ((tputs(tgetstr("up", NULL), 1, ft_put) == ERR))
			return ;
		i++;
	}
	if ((tputs(tgetstr("vi", NULL), 1, ft_put) == ERR)
			|| (tputs(tgetstr("sc", NULL), 1, ft_put) == ERR))
		return ;
	return ;
}

char			*get_final2(char **cmd, t_stop *stop, char *final)
{
	if (stop->cut == 1)
	{
		(cmd[stop->nb]) ? free(cmd[stop->nb]) : 0;
		cmd[stop->nb] = ft_strndup(cmd[stop->nb], how_cut(cmd[stop->nb], 0, 0));
		cmd[stop->nb] = strjoin_free_n(cmd[stop->nb], stop->print, 1);
	}
	else
	{
		if (cmd[stop->nb])
		{
			free(cmd[stop->nb]);
			cmd[stop->nb] = strdup(stop->print);
		}
		else
			stop->add = 1;
	}
	final = to_str(cmd);
	return (final);
}

char			*get_final(char **cmd, t_stop *stop, char *final)
{
	if (cmd[1])
		final = get_final2(cmd, stop, final);
	else if (!cmd[1] && stop->nb > 0)
	{
		final = strdup(cmd[0]);
		final = strjoin_free_n(final, " ", 1);
		final = strjoin_free_n(final, stop->print, 1);
	}
	else
		final = strdup(stop->print);
	if (stop->add == 1)
	{
		final = strjoin_free_n(final, " ", 1);
		final = strjoin_free_n(final, stop->print, 1);
	}
	free_tab(cmd);
	free_stop(stop);
	return (final);
}

char			*begin_comp(char *str, int i, char *final)
{
	t_stop		*stop;
	char		**cmd;
	int			tabi[3];

	tabi[0] = 0;
	tabi[1] = 0;
	tabi[2] = 0;
	(do_space(str)) ? free(str) : 0;
	if (do_space(str))
		return (NULL);
	stop = (t_stop*)malloc(sizeof(t_stop));
	stop_init(stop, str, i);
	stop = core_comp42(str, NULL, stop, tabi);
	if (stop != NULL)
		cmd = split(str, ' ');
	free(str);
	if (stop == NULL)
		return (NULL);
	else
	{
		final = get_final(cmd, stop, final);
		return (final);
	}
}

t_edit			*auto_completion(t_edit *ed, t_froz *fz)
{
	char		*cmd;
	int			i;

	cmd = ed_str(ed, NULL, fz->nb[0] - giv_last(fz));
	while (ed->rpz[2] == 0)
		ed = ed->next;
	i = ed->rpz[2] - giv_last(fz);
	cmd = begin_comp(cmd, i, NULL);
	if (cmd != NULL)
	{
		i = -1;
		free_ed(&ed, fz);
		while (cmd[++i])
			ed = add_ed(ed, cmd[i], NULL, &fz);
		ed = giv_position(ed, giv_last(fz));
		fz->nb[0] = i + giv_last(fz);
		tputs(tgetstr("up", NULL), 0, ft_put);
		tputs(tgetstr("sc", NULL), 0, ft_put);
		tputs(tgetstr("cd", NULL), 0, ft_put);
		free(cmd);
	}
	return (ed);
}
