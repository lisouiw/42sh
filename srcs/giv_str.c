/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   giv_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:48:53 by mallard           #+#    #+#             */
/*   Updated: 2018/05/04 03:43:17 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

char	*ed_str(t_edit *cmd, char *s, int nb)
{
	int		i;

	i = -1;
	while (cmd->rpz[0] == 0)
		cmd = cmd->next;
	if (!(s = (char*)malloc((nb + 1) * sizeof(char))))
		return (NULL);
	while (++i < nb)
	{
		s[i] = cmd->c[0];
		cmd = cmd->next;
	}
	s[i] = '\0';
	return (s);
}

char	*join_cmd_nw(char *cmd, t_edit *ed, t_froz *fz)
{
	char *nw;
	char *tmp;

	nw = NULL;
	if (cmd)
	{
		if (fz->mode[3] != 20 && ed->rpz[0] == 1 && ed->rpz[1] == 1)
			tmp = ft_strjoin(cmd, "\0");
		else
		{
			tmp = NULL;
			nw = ed_str(ed, NULL, fz->nb[0] - giv_last(fz));
			nw = ft_strjoin_free(fz->mode[3] == 20 ? " " : "\n", nw, 2);
			if (fz->mode[3] == 20 && cmd && nw && nw[0] != '\0' && nw[0] != ' ')
				tmp = ft_strjoin_free(ft_strsub(cmd, 0, ft_strlen(cmd) - 2)\
				, nw, 3);
			else if (cmd && nw && nw[0] != '\0')
				tmp = ft_strjoin_free(cmd, nw, 2);
			else
				tmp = ft_strdup(" ");
		}
		free(cmd);
		return (tmp);
	}
	return (ed_str(ed, NULL, fz->nb[0] - giv_last(fz)));
}

char	*join_cmd(char *cmd, t_edit *ed, t_froz *fz)
{
	char *nw;
	char *tmp;

	nw = NULL;
	if (cmd == NULL)
		cmd = ed_str(ed, NULL, fz->nb[0] - giv_last(fz));
	else
	{
		if (ed->rpz[0] == 1 && ed->rpz[1] == 1)
			tmp = ft_strjoin(cmd, "\0");
		else
		{
			nw = ed_str(ed, NULL, fz->nb[0] - giv_last(fz));
			tmp = ft_strjoin_free(cmd, nw, 2);
		}
		free(cmd);
		return (tmp);
	}
	return (cmd);
}
