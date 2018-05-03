/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:31:12 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:31:14 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*w;

	if (!(w = (t_list*)malloc(sizeof(t_list) * (content_size))))
		return (NULL);
	if (content == NULL)
	{
		w->content = NULL;
		w->content_size = 0;
		w->next = NULL;
	}
	else
	{
		w->content = malloc(content_size);
		w->content_size = content_size;
		ft_memcpy(w->content, content, content_size);
		w->next = NULL;
	}
	return (w);
}
