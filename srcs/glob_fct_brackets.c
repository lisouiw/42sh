/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_fct_brackets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:50:53 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:50:54 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

size_t	count_brace(char *s)
{
	int		i;
	int		b;
	size_t	count;

	i = 1;
	b = 1;
	count = 0;
	while (s[++i])
	{
		if (b == 1 && s[i] == ']')
		{
			b = 0;
			++count;
		}
		else if (b == 0 && s[i] == '[')
		{
			i = i + 1;
			b = 1;
		}
	}
	return (count);
}

char	**split_bracket(char *s)
{
	char	**tb;
	size_t	i;
	int		a;
	int		b;

	b = 0;
	a = 0;
	tb = NULL;
	i = count_brace(s);
	if (!(tb = (char**)malloc((i + 1) * sizeof(char*))))
		return (NULL);
	i = -1;
	while (s[a])
	{
		brace_int_count(&a, b, s);
		tb[++i] = ft_strsub(s, b + 1, a - b - 2);
		b = a;
	}
	tb[++i] = NULL;
	return (tb);
}

int		clean_brackets(t_glob **g, t_glob_p **parse)
{
	char	**tb;

	tb = split_bracket((*parse)->cmd);
	if (clean_brackets_star_loop(g, tb, -1, -1))
	{
		free_tab(tb);
		return (2);
	}
	free_tab(tb);
	(*g)->i[1] = 1;
	return (0);
}
