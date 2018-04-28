/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_backslash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 15:12:25 by ltran             #+#    #+#             */
/*   Updated: 2018/04/28 16:45:21 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		last_multiple_char(char *s, char c)
{
    int     i;
    int     a;

    i = ft_strlen(s);
    a = i;
    if (s[i - 1] == 92)
    {
	    while (s[--i] && s[i] == c)
            ;
        if ((a - i + 1) % 2 == 1)
            return (1);
    }
	return (0);
}

int     parse_synthaxe_back(t_cmd *ex)
{
    char    *s;

    while (ex->next != NULL)
        ex = ex->next;
    ex = ex->prev;
    s = ex->cmd;
    if (last_multiple_char(s, 92))
        return (1);       
    return(0);
}
