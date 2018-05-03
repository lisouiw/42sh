/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_brace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:49:19 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:49:20 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

char	*semicolon_translate(t_glob_b *b, char *final)
{
	t_glob_a	*a;

	a = give_semicolon_list(b->m, b, NULL);
	final = join_list_glob_a(a);
	free_glob_a(a);
	return (final);
}

char	*join_semicolon(t_glob_b *b)
{
	char	*final;
	int		st;

	st = 0;
	final = NULL;
	b->cs = giv_brace_s(b->s);
	b->ce = giv_brace_e(b->e);
	final = semicolon_translate(b, NULL);
	final = modif_s_e(b, final);
	return (final);
}

char	*join_two_comas(t_glob_b *b)
{
	char	*final;
	int		num1;
	int		num2;

	final = NULL;
	if (isaltwo(b->cms1, b->cms2))
	{
		if (b->cms1[0] <= b->cms2[0])
			final = join_two_comas_alpha_up(b);
		else
			final = join_two_comas_alpha_down(b);
	}
	else
	{
		num1 = ft_atoi(b->cms1);
		num2 = ft_atoi(b->cms2);
		if (num1 <= num2)
			final = join_two_comas_num_up(b, num1, num2);
		else
			final = join_two_comas_num_down(b, num1, num2);
	}
	return (final);
}

char	*glob_brace_str(t_cmd **ex, t_glob_b *b)
{
	char	*final;

	final = NULL;
	if (brace_semicolon(b->m))
		final = join_semicolon(b);
	else
		final = join_two_comas(b);
	free((*ex)->cmd);
	return (final);
}

char	*glob_brace(t_cmd **ex)
{
	t_glob_b	*b;

	if (!(b = (t_glob_b*)malloc(sizeof(t_glob_b))))
		return ((*ex)->cmd);
	while ((*ex)->cmd[glob_brace_int(ex, b)])
		(*ex)->cmd = glob_brace_str(ex, b);
	free(b);
	return ((*ex)->cmd);
}
