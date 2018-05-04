/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_tool4_comp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:43:30 by mallard           #+#    #+#             */
/*   Updated: 2018/05/04 02:33:44 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_comp42.h"

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

static char			*get_home(t_env *env, int i)
{
	while (env && ft_strcmp(env->name, "HOME="))
		env = env->next;
	if (env && !ft_strcmp(env->name, "HOME=") && i == 2)
		return (ft_strdup(env->ctn));
	if (env && !ft_strcmp(env->name, "HOME=") && i == 1)
		return (ft_strdup("/Users/"));
	return (NULL);
}

static char			*add_home2(char *tmp, t_env *env, char *str)
{
	int				i;

	i = 0;
	if (str[0] == '~' && str[1] == '/')
	{
		tmp = get_home(env, 2);
		if (tmp == NULL)
			return (NULL);
		else
			tmp = strjoin_free_n(tmp, "/", 1);
	}
	else
		tmp = get_home(env, 1);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

char				*add_home(char *str, t_env *env)
{
	char			*new;
	char			*tmp;
	char			*tmp2;

	tmp2 = NULL;
	tmp = NULL;
	tmp = add_home2(tmp, env, str);
	if (tmp == NULL)
		free(str);
	if (tmp == NULL)
		return (NULL);
	if (str[1] == '/' && str[2])
		tmp2 = ft_strdup(&str[2]);
	else if (str[0] == '~' && str[1])
		tmp2 = ft_strdup(&str[1]);
	if (str[1])
		new = strjoin_free_n(tmp, tmp2, 0);
	else
		new = ft_strdup(tmp);
	free(str);
	if (tmp != NULL)
		free(tmp);
	if (tmp2 != NULL)
		free(tmp2);
	return (new);
}
