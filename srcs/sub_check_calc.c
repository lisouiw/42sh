/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_check_calc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:55:01 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:55:03 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int			check_op(char tmp[3], int *error)
{
	if (!tmp[2])
	{
		if (tmp[1] == '/' || (tmp[1] == '*' && tmp[0] != '*'))
		{
			*error = 1;
			return (1);
		}
	}
	else
	{
		if (tmp[0] == tmp[1] || tmp[1] == tmp[2])
		{
			if (tmp[1] == '+' || tmp[1] == '-')
				*error = 2;
			else
			{
				*error = 1;
				return (2);
			}
			return (1);
		}
	}
	return (0);
}

int			check_var(char *var, int *error, int op, int i)
{
	int		c;
	char	tmp[3];
	int		j;

	ft_memset(tmp, '\0', 3);
	while (var[++i])
	{
		if (!ft_isop(var[i]) && !ft_isnumber(var[i]) && !ft_space(var[i]) \
				&& var[i] != '(' && var[i] != ')')
		{
			*error = 1;
			return (i);
		}
		if (ft_isop(var[i]) == 1 && (tmp[op++] = var[i]))
			j = (op == 1) ? i : j;
		if (ft_isnumber(var[i]) == 1 && !(op == 0))
			ft_memset(tmp, '\0', 3);
		if ((tmp[1] || tmp[2]) && (c = check_op(tmp, error)))
			return ((c == 2) ? i : j);
		if (ft_isnumber(var[i]) == 1)
			op = 0;
	}
	return (-1);
}

int			check_list(t_op **op)
{
	t_op	*tmp;
	t_op	*t2;
	t_op	*pls;

	tmp = *op;
	t2 = tmp->next;
	while (tmp->next)
	{
		pls = NULL;
		if ((tmp->x == 0 || tmp->next->x == 0) && tmp->op == '/')
			return (5);
		if (tmp->op == 0 && tmp->next)
		{
			tmp->op = t2->op;
			pls = t2;
			tmp->priority = t2->priority;
			tmp->next = t2->next;
		}
		else
			tmp = tmp->next;
		t2 = t2->next;
		if (pls)
			free(pls);
	}
	return (tmp->op != 0) ? 3 : 0;
}

int			check_long(char *str)
{
	int		i;

	i = (str[0] == '-') ? 1 : 0;
	while (str[i] && ft_isnumber(str[i]))
		i++;
	return (i + 1);
}
