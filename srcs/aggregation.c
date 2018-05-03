/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:42:00 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:42:02 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	aggregation_out(char **t)
{
	if (t[2] == '\0')
		isnumber(t[1]) ? dup2(ft_atoi(t[1]), 1) : parsing_dup_out(t[1], 1);
	else
		isnumber(t[2]) ? dup2(ft_atoi(t[2]), ft_atoi(t[0])) :
			parsing_dup_out(t[2], ft_atoi(t[0]));
	free_tab(t);
}

void	aggregation_in(char **t)
{
	if (t[2] == '\0')
		isnumber(t[1]) ? dup2(0, ft_atoi(t[1])) : parsing_dup_in(t[1], 0);
	else
		isnumber(t[2]) ? dup2(ft_atoi(t[0]), ft_atoi(t[2])) :
			parsing_dup_in(t[2], ft_atoi(t[0]));
	free_tab(t);
}
