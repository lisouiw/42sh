/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:48:22 by mallard           #+#    #+#             */
/*   Updated: 2018/05/04 02:29:06 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

static int	check_option2(char **ta, int *t, int i)
{
	if (ta[t[0]][i] && ta[t[0]][i + 1] == '\\'
		&& ta[t[0]][i + 2] == 'n')
	{
		ft_putchar_fd(ta[t[0]][i], 1);
		i = i + 4;
		ft_putchar_fd('\n', 1);
	}
	if (ta[t[0]][i] && ta[t[0]][i + 1] == '\\'
		&& ta[t[0]][i + 2] == 'r')
	{
		ft_putchar_fd(ta[t[0]][i], 1);
		i = i + 4;
		ft_putchar_fd('\r', 1);
	}
	if (ta[t[0]][i] && ta[t[0]][i + 1] == '\\'
		&& ta[t[0]][i + 2] == 'v')
	{
		ft_putchar_fd(ta[t[0]][i], 1);
		i = i + 4;
		ft_putchar_fd('\v', 1);
	}
	return (i);
}

static int	check_option3(char **ta, int *t, int i)
{
	if (ta[t[0]][i] && ta[t[0]][i + 1] == '\\'
		&& ta[t[0]][i + 2] == 'f')
	{
		ft_putchar_fd(ta[t[0]][i], 1);
		i = i + 4;
		ft_putchar_fd('\f', 1);
	}
	if (ta[t[0]][i] && ta[t[0]][i + 1] == '\\'
		&& ta[t[0]][i + 2] == 'a')
	{
		ft_putchar_fd(ta[t[0]][i], 1);
		i = i + 4;
		ft_putchar_fd('\a', 1);
	}
	if (ta[t[0]][i] && ta[t[0]][i + 1] == '\\'
		&& ta[t[0]][i + 2] == 't')
	{
		ft_putchar_fd(ta[t[0]][i], 1);
		ft_putchar_fd('\t', 1);
		i = i + 4;
	}
	return (i);
}

static int	check_option(char **ta, int *t, int i, int *abis)
{
	if (ta[t[0]][i] && ta[t[0]][i + 1] == '\\'
		&& ta[t[0]][i + 2] == '\\')
	{
		i = i + 4;
		ft_putchar_fd('\\', 1);
	}
	i = check_octal(ta, t, i);
	i = check_option2(ta, t, i);
	i = check_option3(ta, t, i);
	if (ta[t[0]][i] && ta[t[0]][i + 1] == '\\'
		&& ta[t[0]][i + 2] == 'b')
		i = i + 4;
	if (ta[t[0]][i] && ta[t[0]][i + 1] == '\\'
		&& ta[t[0]][i + 2] == 'c')
	{
		ft_putchar_fd(ta[t[0]][i], 1);
		abis[0] = 42;
		return (0);
	}
	return (i);
}

static int	e_flag(char **ta, int *t, int a)
{
	int		i;
	int		abis[2];

	i = 0;
	abis[0] = a;
	while (ta[t[0]])
	{
		while (ta[t[0]][i])
		{
			i = check_option(ta, t, i, abis);
			if (abis[0] == 42)
				return (1);
			if (ta[t[0]][i] == '\0')
				return (a);
			ft_putchar_fd(ta[t[0]][i], 1);
			i++;
		}
		i = 0;
		if (ta[t[0] + 1])
			write(1, " ", 1);
		t[0]++;
	}
	return (a);
}

void		print_tab(char **ta, int i)
{
	int		a;
	int		t[2];

	t[0] = 1;
	a = 0;
	i = 0;
	a = check_echo_flags(ta, t, 0, 0);
	while (ta[t[0]] && (a != 2 && a != 3))
	{
		ft_putstr_fd(ta[t[0]], 1);
		if (ta[t[0] + 1])
			write(1, " ", 1);
		t[0]++;
	}
	if (a == 2 || a == 3)
		a = e_flag(ta, t, a);
	if (a != 1 && a != 3)
		ft_putchar_fd('\n', 1);
	g_ok = 0;
}
