/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:59:15 by mallard           #+#    #+#             */
/*   Updated: 2018/04/27 23:03:51 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

long	ft_atol(const char *str)
{
	unsigned long		nb;
	int					sign;

	nb = 0;
	sign = 1;
	while (*str && (*str == '\n' || *str == '\v' || *str == '\t' ||
				*str == '\f' || *str == '\r' || *str == ' '))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - 48);
		str++;
	}
	return ((long)nb * sign);
}

int		ft_isop(int c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') ? 1 : 0;
}

int		ft_isnumber(int c)
{
	return (c >= '0' && c <= '9') ? 1 : 0;
}

int		ft_space(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || \
			c == '\r' || c == ' ') ? 1 : 0;
}

int		ft_isvip(char c)
{
	return (c == '\'' || c == '"' || c == '\\' || c == '$') ? 1 : 0;
}
