/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:52:50 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:52:51 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	manage_env(t_env *env)
{
	int		nb;
	char	*tmp;

	while (env && ft_strcmp(env->name, "SHLVL="))
		env = env->next;
	if (env != NULL && env->ctn != NULL)
	{
		if ((nb = ft_atoi(env->ctn)))
		{
			nb++;
			tmp = env->ctn;
			env->ctn = ft_itoa(nb);
			free(tmp);
		}
	}
}
