/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_tool4_comp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paoroste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 04:44:54 by paoroste          #+#    #+#             */
/*   Updated: 2018/05/02 13:46:29 by paoroste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_comp42.h"

int					no_bin(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

t_data				*get_prop_rac(t_comp *data, t_data *list, t_stop *stop,
		int *tb)
{
	char			**prop;

	stop->cut = 1;
	data->nb = 0;
	stop->more = 1;
	data->path = get_path2(data, 0, 0, tb);
	if (data->all_prop == 1)
		prop = prop_rac(data->path, NULL, NULL, 0);
	else
		prop = prop_2(data, NULL, 0, NULL);
	free_comp(data);
	if (prop == NULL)
		return (NULL);
	return (get_args(prop, 1, get_high_len(prop), list));
}

static char			*ft_get_home(char *str, int how)
{
	int				i;
	char			*new;

	i = 0;
	if (how == 1)
	{
		new = ft_strdup("/Users/");
	}
	if (how == 2)
	{
		while (str[i] != '=')
			i++;
		new = strdup(&str[i + 1]);
	}
	if (how == 2)
		new = strjoin_free_n(new, "/", 1);
	return (new);
}

static char			*add_home2(char *tmp, char **environ, char *str)
{
	int				i;

	i = 0;
	while (environ[i])
	{
		if (str[0] == '~' && str[1] == '/')
		{
			if (!ft_strncmp(environ[i], "HOME=", 5))
				tmp = ft_get_home(environ[i], 2);
		}
		else
		{
			if (!ft_strncmp(environ[i], "HOME=", 5))
				tmp = ft_get_home(environ[i], 1);
		}
		i++;
	}
	return (tmp);
}

char				*add_home(char *str)
{
	char			*new;
	char			*tmp;
	char			*tmp2;
	extern char		**environ;

	tmp2 = NULL;
	tmp = NULL;
	tmp = add_home2(tmp, environ, str);
	if (str[1] == '/' && str[2])
		tmp2 = ft_strdup(&str[2]);
	else if (str[0] == '~' && str[1])
		tmp2 = ft_strdup(&str[1]);
	if (str[1])
		new = strjoin_free_n(tmp, tmp2, 0);
	else
		new = ft_strdup(tmp);
	free(str);
	free(tmp);
	if (tmp2 != NULL)
		free(tmp2);
	return (new);
}
