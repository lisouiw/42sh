/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_parse_comp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:43:04 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:43:05 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_comp42.h"

char		*cut_path(char *str)
{
	int		i;
	int		repere;
	char	*new;

	repere = 0;
	i = 0;
	while (str[i])
		i++;
	i--;
	while (i != 0)
	{
		if (str[i] == '/')
		{
			repere = i;
			break ;
		}
		i--;
	}
	new = ft_strndup(str, repere + 1);
	return (new);
}

char		*find(char *str, int *tb, char *tmp, char *new)
{
	while (str[tb[0]])
		tb[0]++;
	if (str[tb[0]--] == '/')
		return (strdup(""));
	while (tb[0] >= 0)
	{
		if (str[tb[0]] == '/')
		{
			tb[2] = tb[0] + 1;
			break ;
		}
		tb[0]--;
	}
	(tb[0] > 0) ? tb[1] = -1 : 0;
	while (str[tb[0]++])
		tb[1]++;
	new = (char*)malloc(sizeof(char) * tb[1] + 1);
	tb[1] = 0;
	while (str[tb[2]])
		new[tb[1]++] = str[tb[2]++];
	new[tb[1]] = '\0';
	tmp = ft_strlowcase(new);
	free(new);
	return (tmp);
}

char		*get_path(t_comp *data, int i, int path, int *tabi)
{
	char	*new;

	if (data->cmd[1][0] != ' ')
	{
		while (data->cmd[data->nb][i])
		{
			if (data->cmd[data->nb][i] == '/')
				path = 1;
			if (data->cmd[data->nb][i + 1] == '\0' && (data->cmd[data->nb][i]
						== '/'))
				data->all_prop = 1;
			i++;
		}
		free(data->find);
		data->find = find(data->cmd[data->nb], tabi, NULL, NULL);
	}
	if (data->cmd[1][0] == ' ')
		data->all_prop = 1;
	free(data->path);
	if (path == 1)
		new = cut_path(data->cmd[data->nb]);
	else
		new = strdup("./");
	return (new);
}

char		**init_path(void)
{
	char		**path;

	path = (char**)malloc(sizeof(char*) * 8);
	path[0] = strdup("/usr/bin");
	path[1] = strdup("/bin");
	path[2] = strdup("/usr/sbin");
	path[3] = strdup("/sbin");
	path[4] = strdup("/usr/local/bin");
	path[5] = strdup("/usr/local/munki");
	path[6] = strdup("./");
	path[7] = NULL;
	return (path);
}

char		**parse_select(char *str, t_env *env, char **path, t_stop *stop)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	path = split(str, ' ');
	if (str[i - 1] == ' ' && (!(path[stop->nb])))
	{
		(path) ? free_tab(path) : 0;
		path = (char**)malloc(sizeof(char*) * 3);
		path[0] = strdup(" ");
		path[1] = strdup(" ");
		path[2] = NULL;
		return (path);
	}
	if (path[stop->nb][0] == '~' ||
			(path[stop->nb][0] == '~' && path[stop->nb][1] == '/'))
	{
		path[stop->nb] = add_home(path[stop->nb], env);
		if (path[stop->nb] == NULL)
			free_tab(path);
		if (path[0] == NULL)
			return (NULL);
	}
	return (path);
}
