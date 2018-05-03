/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatmt_here.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:57:06 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:57:08 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		parsing_op_here(char *s, t_cmd **ex, t_froz *fz)
{
	int		i;

	i = 0;
	while (s[i] && s[i] == ' ')
		++i;
	s = replace_nwl_spc(s);
	*ex = separate_cmd(s, i, i, *ex);
	i = parse_type(ex);
	*ex = parse_op_int(*ex, s);
	if ((i = parse_synthaxe(*ex, s)) != 0)
	{
		free(s);
		s = NULL;
		return (i);
	}
	join_redirecting(ex);
	join_ex(ex);
	free(s);
	s = NULL;
	return (check_struct(fz));
}

int		parsing_here(t_edit *ed, t_froz *fz, t_cmd **ex)
{
	*ex = init_ex(NULL);
	while (ed->rpz[0] == 0)
		ed = ed->next;
	if ((fz->mode[3] = parsing_quote(fz->cmd)))
	{
		free_all_ex(ex);
		return (0);
	}
	else if ((fz->mode[3] = parsing_op_here(ft_strdup(fz->cmd), ex, fz)))
	{
		free_all_ex(&(*ex));
		if (!(fz->mode[3] >= 0 && fz->mode[3] <= 6))
			return (error_syntax(fz));
	}
	else if (fz->mode[3] == 0)
		return (1);
	return (0);
}

t_env	*treat_cmd_here(t_env *env, t_edit **cmd, t_his **hs, t_froz **fz)
{
	t_cmd	*ex;

	ex = NULL;
	while ((*cmd)->rpz[0] == 0)
		*cmd = (*cmd)->next;
	if ((*fz)->nb[0] % g_nb->tb[0] != 1)
		ft_putchar('\n');
	if (parsing_here(*cmd, *fz, &ex) == 1)
	{
		add_his(hs, NULL, *fz);
		env = launchcmd(ex, env);
		free_all_ex(&ex);
		free((*fz)->cmd);
		(*fz)->cmd = NULL;
	}
	else if ((*fz)->mode[3] == 0)
	{
		add_his(hs, NULL, *fz);
		free((*fz)->cmd);
		(*fz)->cmd = NULL;
	}
	return (env);
}
