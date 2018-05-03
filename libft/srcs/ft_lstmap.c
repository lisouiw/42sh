/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:31:06 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:31:07 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(f)(t_list *elem))
{
	t_list	*res;
	t_list	*tmp;

	res = f(lst);
	tmp = res;
	while (lst->next)
	{
		lst = lst->next;
		res->next = f(lst);
		res = res->next;
	}
	return (tmp);
}
