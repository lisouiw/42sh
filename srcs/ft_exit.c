/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:48:39 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:48:41 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	ft_exit(char *cmd)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	if (ft_strlen(cmd) > 4)
		exit(42);
	while (cmd && cmd[i])
	{
		if (cmd[i] < '0' || cmd[i] > '9')
			a = 42;
		i++;
	}
	if (a == 42)
	{
		free(cmd);
		exit(255);
	}
	else
		a = ft_atoi(cmd);
	free(cmd);
	if (a >= 0 && a <= 255)
		exit(a);
	exit(42);
}
