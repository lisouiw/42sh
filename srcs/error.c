/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:45:03 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:45:06 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		error_syntax(t_froz *fz)
{
	if (fz->mode[3] == -1 || fz->mode[3] == -2 ||
			(fz->mode[3] <= -6 && fz->mode[3] >= -11))
		ft_putendl_fd("sh: parse error near `\\n'", 2);
	else if (fz->mode[3] == -20)
		ft_putendl_fd("sh: parse error near `&'", 2);
	else if (fz->mode[3] == -3)
		ft_putendl_fd("sh: parse error near `|'", 2);
	else if (fz->mode[3] == -4)
		ft_putendl_fd("sh: parse error near `&&'", 2);
	else if (fz->mode[3] == -5)
		ft_putendl_fd("sh: parse error near `||'", 2);
	else if (fz->mode[3] == -13)
		ft_putendl_fd("sh: parse error near `;'", 2);
	fz->mode[3] = 0;
	return (0);
}

void	error_str(char *error, char *var)
{
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd(var, 2);
}

void	error_op(int error, char *var, t_op *op)
{
	if (error == 1)
	{
		ft_putstr_fd("42sh: bad math expression: operator expected at `", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd("'", 2);
	}
	else if (error == 2)
		ft_putstr_fd("42sh: bad math expression: lvalue required\n", 2);
	else if (error == 3)
	{
		ft_putstr_fd("42sh: bad math expression: operand expected at \n", 2);
		ft_putstr_fd("end of string\n", 2);
	}
	else if (error == 4)
		error_str("bad math expression: operand expected at", var);
	else if (error == 5)
		ft_putstr_fd("42sh: division by zero\n", 2);
	else if (error == 6)
		error_str("number truncated after 19 digits: ", var);
	if (error != 6)
		op->priority = -1;
}
