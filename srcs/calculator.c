/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 01:49:32 by mallard           #+#    #+#             */
/*   Updated: 2018/04/23 20:47:49 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void	error_str(char *error, char *var)
{
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd(var, 2);
}

void	error_op(int error, char *var, t_op *op)
{
	if (error == 1)
		error_str("bad math expression: operator expected at", var);
	else if (error == 2)
		ft_putstr_fd("42sh: bad math expression: lvalue required\n", 2);
	else if (error == 3)
		ft_putstr_fd("42sh: bad math expression: operand expected at end of string\n", 2);
	else if (error == 4)
		error_str("bad math expression: operand expected at", var);
	else if (error == 5)
		ft_putstr_fd("42sh: division by zero\n", 2);
	else if (error == 6)
		error_str("number truncated after 19 digits: ", var);
	if (error != 6)
		op->priority = -1;
}

long	ft_atol(const char *str)
{
	unsigned long 	nb;
	int					sign;

	nb = 0;
	sign = 1;
	while (*str && (*str == '\n' || *str == '\v' || *str == '\t' ||
				*str == '\f' || *str == '\r' || *str == ' '))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - 48);
		str++;
	}
	return ((long)nb * sign);
}

int		ft_isop(int c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') ? 1 : 0;
}

int		ft_isnumber(int c)
{
	return (c >= '0' && c <= '9') ? 1 : 0;
}

int		ft_space(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || \
			c == '\r' ||c == ' ') ? 1 : 0;
}

int		check_op(char tmp[3], int *error)
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
		else
			return (0);
	}
	return (0);
}

int		check_var(char *var, int *error)
{
	int		i;
	int		op;
	int		c;
	char	tmp[3];
	int		j;

	ft_memset(tmp, '\0', 3);
	i = 0;
	op = 0;
	while (var[i])
	{
		if (!ft_isop(var[i]) && !ft_isnumber(var[i]) && !ft_space(var[i]) \
				&& var[i] != '(' && var[i] != ')')
		{
			*error = 1;
			return (i);
		}
		if (ft_isop(var[i]) == 1)
		{
			if (op == 1)
				j = i;
			tmp[op] = var[i];
			op++;
		}
		if (ft_isnumber(var[i]) == 1)
		{
			ft_memset(tmp, '\0', 3);
			op = 0;
		}
		if ((tmp[1] || tmp[2]) && (c = check_op(tmp, error)))
		{
			if (c == 2)
				i = j;
			return (i);
		}
		if (ft_isnumber(var[i]) == 1)
			op = 0;
		i++;
	}
	return (-1);
}

long	operator(long a, long b, char op)
{
	long	i;
	int		ret;

	i = 1;
	if (op == '|')
	{
		ret = a;
		while (++i <= b)
			ret*=a;
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

int		check_list(t_op **op)
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
	if (tmp->op != 0)
		return (3);
	return (0);
}

int		check_long(char *str)
{
	int		i;

	i = (str[0] == '-') ? 1 : 0;
	while (str[i] && ft_isnumber(str[i]))
		i++;
	return (i + 1);
}

int     add_op(t_op **op, char *tmp, int *i, int vip)
{
	t_op    	*t;
	long		x;
	char    	c;
	int     	a;
	int			p;
	char		*str;

	a = (ft_isop(tmp[*i])) ? *i + 1: *i;
	x = ft_atol(tmp + *i);
	if (check_long(tmp + *i) >= 19)
	{
		error_op(6, tmp + *i, *op);
		str = ft_strsub(tmp, *i, 19);
		x = ft_atol(str);
	}
	while (tmp[a] && !ft_isop(tmp[a]))
		a++;
	if (tmp[a] == '*' && tmp[a + 1] == '*')
	{
		c = '|';
		a++;
	}
	else
		c = (tmp[a]) ? tmp[a] : 0;
	if (c == '+' || c == '-')
		p = vip * 3;
	else if (c == '|')
		p = vip * 3 + 2;
	else
		p = vip * 3 + 1;
	*i = a + 1;
	t = op_new(x, c, p);
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

t_op		*op_list(char *var, int vip)
{
	t_op	*op;
	t_op	*new;
	int		i;
	int		j;
	char	*tmp;

	op = NULL;
	i = 0;
	while (var[i])
	{
		j = 0;
		if (var[i] == '(')
		{
			j = bracket(var + i) + i - 1;
			tmp = ft_strsub(var, i + 1, j - i);
			i = j;
			if (op == NULL)
				op = op_list(tmp, vip + 1);
			else
			{
				new = op_list(tmp, vip + 1);
				op_add(&op, new);
			}
		}
		if (var[i] && ft_isop(var[i]) == 1)
			j = add_op(&op, var, &i, vip);
		else if (var[i] &&ft_isnumber(var[i]) == 1)
			j = add_op(&op, var, &i, vip);
		else
			i++;
	}
	return (op);
}

int     op_priority(t_op *op, int priority)
{
	t_op    *t;
	t_op    *t2;
	t_op	*pls;

	t = op;
	t2 = t->next;	

	while (t)
	{
		ft_putendl("00 - loop");
		t = t->next;
	}
	t = op;
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
	t = op;

	while (t)
	{
		ft_putendl("01 - loop");
		t = t->next;
	}
	return (0);
}

t_op		*calculator(char *var)
{
	int		i;
	int		error;
	t_op	*op;
	t_op	*tmp;
	int		vip;

	op = NULL;
	error = 0;
	i = check_var(var, &error);
	if (i != -1)
	{
		op = op_new(0, '-', 1);
		error_op(error, var + i, op);
		return (op);
	}
	if (var[0] == '\0')
		return (op_new(0, '-', 1));
	else
	{
		op = NULL;
		op = op_list(var, 0);
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
	return (op_new(0, '-', -1));
}
