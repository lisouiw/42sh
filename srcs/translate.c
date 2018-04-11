/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 13:54:02 by mallard           #+#    #+#             */
/*   Updated: 2018/04/11 14:10:18 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

char		**translate(t_env *env, char *cmd)
{
	char	**arg;

	arg = NULL;
	if (loopy_loop(&cmd, env) != -1)
		return (arg);
	else
		arg = NULL;
	return (arg);
}
