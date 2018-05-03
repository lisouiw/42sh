/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_brace_two_comas.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:50:26 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:50:29 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

char	*join_two_comas_num_down(t_glob_b *b, int num1, int num2)
{
	char	*final;

	final = NULL;
	b->cs = giv_brace_s(b->s);
	b->ce = giv_brace_e(b->e);
	while (num1 >= num2)
	{
		if (final == NULL)
			final = join_brace_nf(b, b->cms1);
		else
			final = strjoin_free_n(strjoin_free_n(final, " ", 1),
				join_brace(b, ft_itoa(num1)), 3);
		--num1;
	}
	final = modif_s_e(b, final);
	free(b->cms1);
	free(b->cms2);
	return (final);
}

char	*join_two_comas_num_up(t_glob_b *b, int num1, int num2)
{
	char	*final;

	final = NULL;
	b->cs = giv_brace_s(b->s);
	b->ce = giv_brace_e(b->e);
	while (num1 <= num2)
	{
		if (final == NULL)
			final = join_brace_nf(b, b->cms1);
		else
			final = strjoin_free_n(strjoin_free_n(final, " ", 1),
				join_brace(b, ft_itoa(num1)), 3);
		++num1;
	}
	final = modif_s_e(b, final);
	free(b->cms1);
	free(b->cms2);
	return (final);
}

char	*join_brace_nf(t_glob_b *b, char *final)
{
	if (b->cs != NULL && b->ce != NULL)
		final = strjoin_free_n(strjoin_free_n(b->cs, final, 0), b->ce, 1);
	else if (b->cs != NULL)
		final = strjoin_free_n(b->cs, final, 0);
	else if (b->ce != NULL)
		final = strjoin_free_n(final, b->ce, 0);
	else
		return (ft_strdup(final));
	return (final);
}

char	*join_two_comas_alpha_down(t_glob_b *b)
{
	char	*final;

	final = NULL;
	b->cs = giv_brace_s(b->s);
	b->ce = giv_brace_e(b->e);
	while (b->cms1[0] >= b->cms2[0])
	{
		if (final == NULL)
			final = join_brace_nf(b, b->cms1);
		else
			final = strjoin_free_n(strjoin_free_n(final, " ", 1),
				join_brace_nf(b, b->cms1), 3);
		b->cms1[0] = b->cms1[0] - 1;
	}
	final = modif_s_e(b, final);
	return (final);
}

char	*join_two_comas_alpha_up(t_glob_b *b)
{
	char	*final;

	final = NULL;
	b->cs = giv_brace_s(b->s);
	b->ce = giv_brace_e(b->e);
	while (b->cms1[0] <= b->cms2[0])
	{
		if (final == NULL)
			final = join_brace_nf(b, b->cms1);
		else
			final = strjoin_free_n(strjoin_free_n(final, " ", 1),
				join_brace_nf(b, b->cms1), 3);
		b->cms1[0] = b->cms1[0] + 1;
	}
	final = modif_s_e(b, final);
	free(b->cms1);
	free(b->cms2);
	return (final);
}
