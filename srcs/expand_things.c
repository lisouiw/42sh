/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybensimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 16:16:45 by ybensimo          #+#    #+#             */
/*   Updated: 2018/04/07 12:01:43 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var(char *str, char c, t_sh *sh)
{
	char	*var;
	int		i;
	int		safe;

	(void)sh;
	i = 0;
	if ((var = ft_memalloc(ft_strlen(str))) == NULL)
		malloc_error();
	if (c == ' ')
	{
		while (str[i] && str[i] != ' ' && str[i] != '\v' && str[i] != '\t')
		{
			var[i] = str[i];
			i++;
		}
		var[i] = '\0';
	}
	else
	{
		i++;
		safe = 0;
		if (str[i] && str[i] != c)
		{
			while (str[i] && str[i] != c)
			{
				var[safe++] = str[i];
				i++;
			}
			var[safe] = '\0';
		}

	}
	return (var);
}

int		expand_things(t_sh *sh, char *cur, int *s, t_token *tok)
{
	char	*var;
	int		ret;
	int		i;

	if (!cur[1] || cur[1] == ' ')
	{
		tok->str[*s] = '$';
		(*s)++;
		return (1);
	}
	else if (cur[1] == '(')
	{
		var = get_var(cur + 1, ')', sh);
		ret = ft_strlen(var) + 2;
	}
	else if (cur[1] == '{')
	{
		var = get_var(cur + 1, '}', sh);
		ret = ft_strlen(var) + 2;
		if (var[0])
		{
			find_variable(sh, var, tok, ft_strlen(cur));
			(*s) = ft_strlen(tok->str);
		}
		else
		{
			ft_fprintf(2, "42sh: bad substitution\n");
			clean_lines(sh);
			return (-1);
		}
	}
	else if (cur[1] == '[')
	{
		var = get_var(cur + 1, ']', sh);
		i = calculator(var, tok);
		(*s) = ft_strlen(var);
		ret = ft_strlen(var) + 2;
		if (i == - 1)
			clean_lines(sh);
		while (cur[i] && ++i != ret)
			cur[i] = ' ';
	}
	else
	{
		var = get_var(cur + 1, ' ', sh);
		ret = ft_strlen(var) + 1;
		find_variable(sh, var, tok, ft_strlen(cur));
		if (var[0])
		{
			printf("var = %s\n", var);
			(*s) = ft_strlen(tok->str);
		}
		else
		{
			ft_fprintf(2, "42sh: bad substitution\n");
			clean_lines(sh);
			return (-1);
		}
	}
	return (ret);
}
