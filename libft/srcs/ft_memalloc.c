/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:31:23 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:31:24 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memalloc(size_t size)
{
	char	*mo;

	mo = (char *)malloc(size * sizeof(mo));
	if (!(mo))
		return (NULL);
	ft_bzero(mo, size);
	return (mo);
}
