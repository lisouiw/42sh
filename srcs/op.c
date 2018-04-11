/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 01:45:49 by mallard           #+#    #+#             */
/*   Updated: 2018/04/10 17:04:22 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

// + - --> 0
// * / % --> 1
// ^ --> 2
// () priority + 3

t_op		*op_new(long x, char op, int priority)
{
	t_op	*new;

	if (!(new = (t_op *)malloc(sizeof(t_op))))
		exit(1);
	new->x = x;
	new->op = op;
	new->priority = priority;
	new->next = NULL;
	return (new);
}

void		op_add(t_op **op, t_op *new)
{
	t_op 	*tmp;

	if (new)
	{
		tmp = *op;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int			check_priority(t_op *op)
{
	t_op	*tmp;
	int		max;

	tmp = op;
	max = 0;
	while (tmp)
	{
		if (max < tmp->priority && tmp->next)
			max = tmp->priority;
		tmp = tmp->next;
	}
	return (max);
}
