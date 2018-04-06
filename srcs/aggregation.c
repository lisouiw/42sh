/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:14:58 by ltran             #+#    #+#             */
/*   Updated: 2018/04/06 15:09:46 by ltran            ###   ########.fr       */
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
