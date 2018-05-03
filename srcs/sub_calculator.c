/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_calculator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:54:51 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:54:52 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

long		operator(long a, long b, char op)
{
	long	i;
	int		ret;

	i = 1;
	if (op == '|')
	{
		ret = a;
		while (++i <= b)
			ret *= a;
		return (ret);
	}
	if (op == '+')
		return (a + b);
	if (op == '-')
		return (a - b);
	if (op == '*')
		return (a * b);
	if (op == '/')
		return (a / b);
	if (op == '%')
		return (a % b);
	return (-1);
}

void		set_op(char c, int *vip)
{
	if (c == '+' || c == '-')
		*vip = *vip * 3;
	else if (c == '|')
		*vip = *vip * 3 + 2;
	else
		*vip = *vip * 3 + 1;
}

t_op		*cal2(t_op *op, char *var)
{
	int		vip;
	int		error;
	t_op	*tmp;

	op = op_list(var, 0, 0);
	if (op == NULL)
		return (op_new(0, '-', -1));
	vip = check_priority(op);
	error = check_list(&op);
	if (error != 0)
	{
		error_op(error, var, op);
		return (op);
	}
	while (vip >= 0)
	{
		op_priority(op, vip);
		vip--;
	}
	tmp = op_new(op->x, 0, 1);
	free_op(&op);
	return (tmp);
}

t_op		*calculator(char *var)
{
	int		i;
	int		error;
	t_op	*op;

	op = NULL;
	error = 0;
	i = check_var(var, &error, 0, -1);
	if (i != -1)
	{
		op = op_new(0, '-', 1);
		error_op(error, var + i, op);
		return (op);
	}
	if (var[0] == '\0')
		return (op_new(0, '-', 1));
	else
		op = cal2(op, var);
	return (op);
}
