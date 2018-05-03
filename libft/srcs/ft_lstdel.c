/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:30:45 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:30:47 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*sup;

	sup = *alst;
	if (!alst || !del)
		return ;
	while (sup)
	{
		del(sup->content, sup->content_size);
		free(sup);
		sup = sup->next;
	}
	*alst = NULL;
}
