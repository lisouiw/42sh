/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:48:31 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:48:33 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	print_octal(int nb)
{
	if (nb >= 41 && nb <= 47)
		ft_putchar_fd(nb - 8, 1);
	if (nb >= 50 && nb <= 57)
		ft_putchar_fd(nb - 10, 1);
	if (nb >= 60 && nb <= 67)
		ft_putchar_fd(nb - 12, 1);
	if (nb >= 70 && nb <= 77)
		ft_putchar_fd(nb - 14, 1);
	if (nb >= 100 && nb <= 107)
		ft_putchar_fd(nb - 36, 1);
	if (nb >= 110 && nb <= 117)
		ft_putchar_fd(nb - 38, 1);
	if (nb >= 120 && nb <= 127)
		ft_putchar_fd(nb - 40, 1);
	if (nb >= 130 && nb <= 137)
		ft_putchar_fd(nb - 42, 1);
	if (nb >= 140 && nb <= 147)
		ft_putchar_fd(nb - 44, 1);
	if (nb >= 150 && nb <= 157)
		ft_putchar_fd(nb - 46, 1);
	if (nb >= 160 && nb <= 167)
		ft_putchar_fd(nb - 48, 1);
	if (nb >= 170 && nb <= 176)
		ft_putchar_fd(nb - 50, 1);
}

int		check_octal3(char *str, int i, char **ta, int *t)
{
	int nb;

	nb = ft_atoi(str);
	ft_putchar_fd(ta[t[0]][i - 4], 1);
	print_octal(nb);
	free(str);
	return (i);
}

int		check_octal2(char *str, int i, char **ta, int *t)
{
	int nb;

	nb = ft_atoi(str);
	ft_putchar_fd(ta[t[0]][i - 5], 1);
	print_octal(nb);
	free(str);
	return (i);
}

int		check_octal42(char **ta, int *t, int i, char *str_nb)
{
	if (ta[t[0]][i + 2] >= '0' && ta[t[0]][i + 2] <= '9')
		str_nb[0] = ta[t[0]][i + 2];
	else
	{
		free(str_nb);
		return (i);
	}
	if (ta[t[0]][i + 3] >= '0' && ta[t[0]][i + 3] <= '9')
		str_nb[1] = ta[t[0]][i + 3];
	else
	{
		ft_putchar_fd(ta[t[0]][i], 1);
		return (i + 4);
	}
	if (ta[t[0]][i + 4] >= '0' && ta[t[0]][i + 4] <= '9')
	{
		str_nb[2] = ta[t[0]][i + 4];
		return (check_octal2(str_nb, i + 5, ta, t));
	}
	else
		return (check_octal3(str_nb, i + 4, ta, t));
	free(str_nb);
	return (i);
}

int		check_octal(char **ta, int *t, int i)
{
	char	*str_nb;

	str_nb = ft_memalloc(4);
	if (ta[t[0]][i] && ta[t[0]][i + 1] == '\\')
		return (check_octal42(ta, t, i, str_nb));
	free(str_nb);
	return (i);
}
