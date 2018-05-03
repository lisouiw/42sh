/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_tool3_comp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:43:22 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:43:23 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_comp42.h"

int				how_cut(char *str, int i, int len)
{
	if ((str[0] == '/' || str[0] == '~') && (!str[1]))
		return (1);
	if (str[0] == '/')
	{
		while (str[i])
		{
			if (str[i + 1] == '/')
				break ;
			i++;
		}
		if (str[i] == '\0')
			return (1);
	}
	while (str[i])
		i++;
	while (i > 0)
	{
		if (str[i] == '/' || IS_SPACE(str[i]))
		{
			len = (i + 1);
			break ;
		}
		i--;
	}
	return (len);
}

char			*to_str(char **cmd)
{
	int			i;
	char		*final;

	i = 1;
	final = strdup(cmd[0]);
	while (cmd[i])
	{
		final = strjoin_free_n(final, " ", 1);
		final = strjoin_free_n(final, cmd[i], 1);
		i++;
	}
	return (final);
}

void			data_init(t_comp *data)
{
	data->str = ft_strlowcase(data->cmd[0]);
	data->d_name = strdup("");
	data->in_path = init_path();
	data->find = strdup("");
	data->path = strdup("");
}

void			free_stop(t_stop *stop)
{
	free(stop->print);
	free(stop);
}

int				where_am_i(char *str, int i)
{
	int			nb;
	int			c;

	nb = 0;
	c = 0;
	while (IS_SPACE(str[c]) && c < i)
		c++;
	while (c < i)
	{
		if (IS_SPACE(str[c]))
		{
			while (c < i)
			{
				if (!IS_SPACE(str[c]) || str[c + 1] == '\0')
				{
					nb++;
					break ;
				}
				c++;
			}
		}
		c++;
	}
	return (nb);
}
