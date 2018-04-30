/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corosteg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 18:50:37 by corosteg          #+#    #+#             */
/*   Updated: 2018/04/30 18:52:12 by corosteg         ###   ########.fr       */
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
