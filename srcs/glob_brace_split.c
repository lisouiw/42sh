/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_brace_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:50:14 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:50:16 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

char	*modif_s_e(t_glob_b *b, char *final)
{
	char	*tmp;
	char	*tmp1;

	if (b->cs)
	{
		tmp = ft_strsub(b->s, 0, ft_strlen(b->s) - ft_strlen(b->cs));
		free(b->s);
		b->s = tmp;
		free(b->cs);
	}
	if (b->ce)
	{
		tmp1 = ft_strsub(b->e, ft_strlen(b->ce),
			ft_strlen(b->e) - ft_strlen(b->ce));
		free(b->e);
		b->e = tmp1;
		free(b->ce);
	}
	final = strjoin_free_n(b->s, strjoin_free_n(final, b->e, 3), 3);
	free(b->m);
	return (final);
}

char	*giv_brace_e(char *s)
{
	int		d;
	int		i;

	i = -1;
	if (s[++i] == ' ' || !s[i])
		return (NULL);
	d = i;
	while (s[++d] && s[d] != ' ')
		;
	return (ft_strsub(s, i, d - i));
}

char	*giv_brace_s(char *s)
{
	int		d;
	int		i;

	i = ft_strlen(s);
	if (s[--i] == ' ' || !s[i])
		return (NULL);
	d = i;
	while (s[--d] && s[d] != ' ')
		;
	return (ft_strsub(s, d + 1, i - d));
}

char	*join_brace(t_glob_b *b, char *final)
{
	if (b->cs != NULL && b->ce != NULL)
		final = strjoin_free_n(strjoin_free_n(b->cs, final, 2), b->ce, 1);
	else if (b->cs != NULL)
		final = strjoin_free_n(b->cs, final, 2);
	else if (b->ce != NULL)
		final = strjoin_free_n(final, b->ce, 1);
	return (final);
}
