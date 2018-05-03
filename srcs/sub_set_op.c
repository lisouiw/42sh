/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_set_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:55:35 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:55:36 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int			add_op(t_op **op, char *tmp, int *i, int vip)
{
	t_op	*t;
	long	x;
	char	c;
	int		a;
	char	*str;

	a = (ft_isop(tmp[*i])) ? *i + 1 : *i;
	x = ft_atol(tmp + *i);
	if (check_long(tmp + *i) >= 19)
	{
		error_op(6, tmp + *i, *op);
		str = ft_strsub(tmp, *i, 19);
		x = ft_atol(str);
	}
	while (tmp[a] && !ft_isop(tmp[a]))
		a++;
	if (tmp[a] == '*' && tmp[a + 1] == '*' && (c = '|'))
		a++;
	else
		c = (tmp[a]) ? tmp[a] : 0;
	set_op(c, &vip);
	*i = a + 1;
	t = op_new(x, c, vip);
	(*op == NULL) ? *op = t : op_add(op, t);
	return (0);
}

int			bracket(char *var)
{
	int		i;
	int		b;

	i = 0;
	b = 0;
	while (var[i])
	{
		if (var[i] == '(')
			b++;
		if (var[i] == ')')
			b--;
		if (b == 0)
			return (i);
		i++;
	}
	return (0);
}

t_op		*op_list(char *var, int vip, int i)
{
	t_op	*op;
	t_op	*new;
	int		j;
	char	*tmp;

	op = NULL;
	while (var[i] && !(j = 0))
	{
		if (var[i] == '(')
		{
			j = bracket(var + i) + i - 1;
			tmp = ft_strsub(var, i + 1, j - i);
			i = j;
			new = op_list(tmp, vip + 1, 0);
			(op == NULL) ? new = op : op_add(&op, new);
			ft_strdel(&tmp);
		}
		if (var[i] && ft_isop(var[i]) == 1)
			j = add_op(&op, var, &i, vip);
		else if (var[i] && ft_isnumber(var[i]) == 1)
			j = add_op(&op, var, &i, vip);
		else
			i++;
	}
	return (op);
}

int			op_priority(t_op *op, int priority)
{
	t_op	*t;
	t_op	*t2;
	t_op	*pls;

	t = op;
	t2 = t->next;
	while (t && t2)
	{
		pls = NULL;
		if (t->priority == priority)
		{
			t->x = operator(t->x, t2->x, t->op);
			t->op = t2->op;
			t->priority = t2->priority;
			pls = t2;
			t->next = t2->next;
		}
		else
			t = t->next;
		t2 = t2->next;
		if (pls)
			free(pls);
	}
	return (0);
}
