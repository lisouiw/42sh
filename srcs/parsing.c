/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 13:09:16 by ltran             #+#    #+#             */
/*   Updated: 2018/04/23 19:56:37 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

char    *replace_nwl_spc(char *s)
{
    int        i;
    int        q;

    q = 0;
    i = -1;
    while (s[++i])
    {
        if ((i > 0 && s[i - 1] != '/') && s[i] == 39 && q != 2)
            q = (q == 1) ? 0 : 1;
        else if ((i > 0 && s[i - 1] != '/') && s[i] == 34 && q != 1)
            q = (q == 2) ? 0 : 2;
        else if (s[i] == '\n' && q == 0)
            s[i] = ' ';
    }
    return (s);
}

int		parsing_op(char *s, t_cmd **ex, t_froz *fz)
{
	int		i;

	i = 0;
	while (s[i] && s[i] == ' ')
		++i;
	s = replace_nwl_spc(s);
	*ex = separate_cmd(s, i, i, *ex);
	i = parse_type(ex);
	*ex = parse_op_int(*ex, s);
	if ((i = parse_synthaxe(*ex)) != 0)
	{
		free(s);
		return (i);
	}
	join_redirecting(ex);
	join_ex(ex);
	print_ex_up(*ex);
	free(s);
    s = NULL;
	return (add_delim(fz, *ex));
}

int        parsing_quote(char *s)
{
    int        i;
    int        a;

    i = 0;
    a = -1;
	ft_putstr(s);
    while (s[++a])
    {
        if (i != 1 && a > 0 && s[a - 1] != 47 && s[a] == '"')
            i = (i == 0) ? 2 : 0;
        else if (i != 2 && a > 0 && s[a - 1] != 47 && s[a] == 39)
            i = (i == 0) ? 1 : 0;
    }
    return (i);
}

int		parsing(t_edit *ed, t_froz *fz, t_cmd **ex)
{
	*ex = init_ex(NULL);
	if (fz->mode[3] == 6)
		add_doc(fz, ed_str(ed, NULL, fz->nb[0] - giv_last(fz)));
	else
		fz->cmd = join_cmd_nw(fz->cmd, ed, fz);
	while (ed->rpz[0] == 0)
		ed = ed->next;
	if ((fz->mode[3] = parsing_quote(fz->cmd)))
	{
		free_all_ex(ex);
		return (0);
	}
	else if ((fz->mode[3] = parsing_op(ft_strdup(fz->cmd), ex, fz)))
	{
		free_all_ex(&(*ex));
		if (!(fz->mode[3] >= 0 && fz->mode[3] <= 6) && fz->mode[3] != 20)
			return (error_syntax(fz));
	}
	else if (fz->mode[3] == 0)
		return (1);
	return (0);
}
