/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 13:31:51 by ltran             #+#    #+#             */
/*   Updated: 2018/04/05 16:42:43 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		if_only_i(char *s, char c)
{
	int		i;

	i = -1;
	while (s[++i] && s[i] == c)
		;
	if (s[i] == '\0')
	{
		if (s)
			free(s);
		return (1);
	}
	if (s)
		free(s);
	return (0);
}

int		if_chr_ex(char *s, char c)
{
	int		i;

	i = -1;
	while (s[++i] && s[i] != c)
		;
	if (s[i] == c)
		return (1);
	return (0);
}

int		if_only(char *s, char c)
{
	while (s && *s == c)
		++s;
	if (!(*s))
		return (1);
	return (0);
}

void	ecriture_info(t_env *lst)
{
	if (!(lst))
		return ;
	while (lst->next != NULL)
	{
		ft_putstr_fd(lst->name, 1);
		ft_putendl_fd(lst->ctn, 1);
		lst = lst->next;
	}
	ft_putstr_fd(lst->name, 1);
	ft_putendl_fd(lst->ctn, 1);
}

int		white_space(char *s)
{
	int		i;

	i = -1;
	if (s[i + 1] != ' ' && s[i + 1] != '\t')
		return (0);
	while (s[++i] && (s[i] == ' ' || s[i] == '\t'))
		;
	return (i);
}
