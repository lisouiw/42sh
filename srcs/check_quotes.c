/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 04:40:31 by ybensimo          #+#    #+#             */
/*   Updated: 2018/02/21 02:32:47 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cat_lines(t_sh *sh, int n)
{
	char	*tmp;

	if (n == 2)
	{
		sh->curline[sh->linelen - 1] = '\0';
		tmp = ft_sprintf("%s%s", sh->completeline, sh->curline);
	}
	else if (n == 1)
		tmp = ft_sprintf("%s%s\n", sh->completeline, sh->curline);
	else
		tmp = ft_sprintf("%s%s", sh->completeline, sh->curline);
	free(sh->completeline);
	sh->completeline = tmp;
	free(sh->curline);
	sh->curline = NULL;
	//	sh->completeline = ft_strdup(tmp);
	//	free(tmp);
}

static int	insert(char *curline, int i)
{
	char	*tmp;
	int		a;

	if (!(tmp = ft_strnew(ft_strlen(curline))))
		return (-1);
	ft_bzero(tmp, ft_strlen(curline));
	a = 0;
	while (curline[i])
	{
		if (curline[i] == '{' || curline[i] == '[' || curline[i] == '(')
		{
			if (tmp[0] == '{')
			{
				free(tmp);
				return (-1);
			}
			tmp[a] = curline[i];
			a++;
		}
		if (curline[i] == '}' || curline[i] == ']' || curline[i] == ')')
		{
			a = (a == 0) ? a : a - 1;
			if (tmp[0] == '\0' || (curline[i] != tmp[a] + 1 && curline[i] != tmp[a] + 2))
			{
				free(tmp);
				return (-1);
			}
			tmp[a] = '\0';
		}
		i++;
	}
	if (tmp[0] != '\0')
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}

static int	loopy_loop(t_sh *sh)
{
	int		i;
	int		j;

	i = 0;
	while (sh->curline[i])
	{
		if (sh->curline[i] == '$' && !sh->isinsquote)
		{
			if (sh->curline[i + 1] && sh->curline[i + 1] == '{')
			{
				j = i + 1;
				while (sh->curline[i] && sh->curline[i] != '}')
					i++;
				if (!sh->curline[i])
				{
					ft_fprintf(2, "42sh: lacking closing }\n");
					clean_lines(sh);
					return (-1);
				}
				if (insert(sh->curline, j) == -1)
				{
					ft_fprintf(2, "42sh: %s: bad substitution\n", sh->curline + j - 1);
					clean_lines(sh);
					return (-1);
				}
			}
			else if (sh->curline[i + 1] && sh->curline[i + 1] == '(')
			{
				j = i + 1;
				while (sh->curline[i] && sh->curline[i] != ')')
					i++;
				if (!sh->curline[i])
				{
					ft_fprintf(2, "42sh: lacking closing )\n");
					clean_lines(sh);
					return (-1);
				}
				if (insert(sh->curline, j) == -1)
				{
					ft_fprintf(2, "42sh: %s: bad substitution\n", sh->curline + j - 2);
					clean_lines(sh);
					return (-1);
				}
			}
			else if (sh->curline[i + 1] && sh->curline[i + 1] == '[')
			{
				j = i + 1;
				while (sh->curline[i] && sh->curline[i] != ']')
					i++;
				if (!sh->curline[i])
				{
					ft_fprintf(2, "42sh: lacking closing [\n");
					clean_lines(sh);
					return (-1);
				}
				if (insert(sh->curline, j) == -1)
				{
					ft_fprintf(2, "42sh: %s: bad substitution\n", sh->curline + j - 2);
					clean_lines(sh);
					return (-1);
				}
			}
		}
		else if (sh->curline[i] == '\'' && !sh->isindquote)
			sh->isinsquote = (sh->isinsquote ? 0 : 1);
		else if (sh->curline[i] == '"' && !sh->isinsquote)
			sh->isindquote = (sh->isindquote ? 0 : 1);
		else if (sh->curline[i] == '\\' && !sh->isinsquote)
		{
			if (sh->curline[i + 1])
				i++;
		}
		i++;
	}
	return (i);
}
/*
   void		rm_bslash(t_sh *sh)
   {
   char	*new;

   new = ft_strndup(sh->completeline, ft_strlen(sh->completeline) - 1);
   free(sh->completeline);
   sh->completeline = new;
   }
   */
void		check_quotes(t_sh *sh)
{
	int		i;

	//	cat_lines(sh);
	//	loopy_loop(sh);
	if ((i = loopy_loop(sh)) != -1)
	{
		if (sh->isindquote)
		{
			cat_lines(sh, 1);
			ft_dquote(sh);
		}
		else if (sh->isinsquote)
		{
			cat_lines(sh, 1);
			ft_squote(sh);
		}
		else if (((i - 1 >= 0) && (sh->curline[i - 1] == '\\')) || (!ft_strcmp(sh->completeline, "\\\n") && !sh->isbslash))
		{
			cat_lines(sh, 2);
			//		rm_bslash(sh);
			sh->isbslash = 1;
			ft_bslash(sh);
		}
		else if (ft_strlen(sh->completeline) > 1 || ft_strlen(sh->curline) > 1)
		{
			cat_lines(sh, 0);
			//			if (tcsetattr(0, TCSANOW, &sh->origin) < 0)
			//			{
			//				ft_fprintf(sh->ttfd, "42sh: an error occured with the termcaps.\n");
			//				clean_exit(sh);
			//			}
			split_semi_colon(sh);
		}
		else
		{
			clean_lines(sh);
			//	free(sh->curline);
			//	sh->curline = NULL;
			//	free(sh->completeline);
			//	sh->completeline = NULL;
		}
	}
}
