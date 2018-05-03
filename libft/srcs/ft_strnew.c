/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:37:05 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 13:37:06 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnew(size_t size)
{
	char				*new;

	new = (char*)malloc(sizeof(char) * (size + 1));
	if (!(new))
		return (NULL);
	ft_bzero(new, size + 1);
	return (new);
}
