/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corosteg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 17:55:54 by corosteg          #+#    #+#             */
/*   Updated: 2018/04/29 19:43:10 by corosteg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int				check_echo_flags2(char **cd, int *tab1, int a, int b)
{
	if ((cd[tab1[0]][a] == 'n' && b == 2) || (b == 1 && cd[tab1[0]][a] == 'e'))
		b = 3;
	if (cd[tab1[0]][a] == 'n' && b == 0)
		b = 1;
	if (cd[tab1[0]][a] == 'e' && b == 0)
		b = 2;
	return (b);
}

int				check_echo_flags(char **cd, int *tab1, int a, int b)
{
	int		final;

	while (cd[tab1[0]] && cd[tab1[0]][0] == '-')
	{
		while (cd[tab1[0]][++a])
		{
			if ((cd[tab1[0]][a] != '-' && cd[tab1[0]][a] != 'e' &&
				cd[tab1[0]][a] != 'n') || (cd[tab1[0]][a] == '-'
				&& cd[tab1[0]][a + 1] == '-'))
				if (cd[tab1[0]][a] == '-' || cd[tab1[0]][a] != 'n'
					|| cd[tab1[0]][a] != 'e')
				{
					if (tab1[0] > 1)
						return (final);
					else
						return (0);
					return (b);
				}
			b = check_echo_flags2(cd, tab1, a, b);
		}
		final = b;
		a = -1;
		tab1[0]++;
	}
	return (final);
}

int				check_n(char **ta, int *t, int a)
{
	int i;
	int b;

	i = t[0];
	b = 0;
	while (ta[i])
	{
		while (ta[i][b])
		{
			if (ta[i][b] == '\n')
			{
				if (a == 3)
					return (2);
				if (a == 1)
					return (0);
			}
			b++;
		}
		b = 0;
		i++;
	}
	return (a);
}
