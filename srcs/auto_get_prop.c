/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_get_prop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:42:54 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:42:56 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_comp42.h"

static char		**prop22(t_comp *data, struct dirent *file, DIR *rep, int nb)
{
	int		i;
	char	**prop;

	i = 0;
	prop = NULL;
	while (data->in_path[i])
	{
		if (!(rep = opendir(data->in_path[i])))
			return (NULL);
		while ((file = readdir(rep)) != NULL)
		{
			free(data->d_name);
			data->d_name = ft_strlowcase(file->d_name);
			if (ft_strncmp(data->str, data->d_name,
						ft_strlen(data->str)) == 0)
				nb++;
		}
		closedir(rep);
		i++;
	}
	if (nb > 0)
		(prop = (char**)malloc(sizeof(char*) * (nb + 1)));
	else
		return (NULL);
	return (prop);
}

t_data			*get_prop2(t_comp *data, t_data *list, t_stop *stop, int *tb)
{
	char		**prop;
	int			i;

	i = 0;
	if (no_bin(data->cmd[0]) == 1)
		return (get_prop_rac(data, list, stop, tb));
	prop = prop22(data, NULL, NULL, 0);
	if (prop == NULL)
	{
		free_comp(data);
		return (NULL);
	}
	prop = get_prop2_2(data, i, prop, NULL);
	free_comp(data);
	if (prop == NULL)
		return (NULL);
	return (get_args(prop, 1, get_high_len(prop), list));
}

char			**prop_rac(char *path, struct dirent *file, DIR *rep, int nb)
{
	char		**prop;

	if (!(rep = opendir(path)))
		return (NULL);
	while ((file = readdir(rep)) != NULL)
		nb++;
	closedir(rep);
	if (nb > 2)
		(prop = (char**)malloc(sizeof(char*) * (nb - 1)));
	else
		return (NULL);
	if (!(rep = opendir(path)))
		return (NULL);
	nb = -2;
	while ((file = readdir(rep)) != NULL)
	{
		(nb >= 0) ? prop[nb] = strdup(file->d_name) : 0;
		if (file->d_type == 4 && nb >= 0)
			prop[nb] = strjoin_free_n(prop[nb], "/", 1);
		nb++;
	}
	prop[nb] = NULL;
	closedir(rep);
	return (prop);
}

char			**prop_2(t_comp *data, struct dirent *file, int i, DIR *rep)
{
	char		**prop;

	if (!(rep = opendir(data->path)))
		return (NULL);
	while ((file = readdir(rep)) != NULL)
	{
		free(data->d_name);
		data->d_name = ft_strlowcase(file->d_name);
		if (ft_strncmp(data->find, data->d_name,
					ft_strlen(data->find)) == 0)
			i++;
	}
	closedir(rep);
	if (i > 0)
		(prop = (char**)malloc(sizeof(char*) * (i + 1)));
	else
		return (NULL);
	if (!(rep = opendir(data->path)))
		return (NULL);
	prop = prop_2_2(file, data, prop, rep);
	if (prop == NULL)
		return (NULL);
	return (prop);
}

t_data			*get_prop(char *str, t_stop *stop, t_data *list, t_env *env)
{
	t_comp		*data;
	char		**prop;
	int			tabi[3];

	tabi[0] = 0;
	tabi[1] = 0;
	tabi[2] = 0;
	data = (t_comp*)malloc(sizeof(t_comp));
	data->cmd = parse_select(str, env, NULL, stop);
	if (data->cmd == NULL)
	{
		free(data);
		return (NULL);
	}
	data_init(data);
	if ((data->cmd[0] && data->cmd[1]))
		prop = get_prop22(stop, data, NULL, tabi);
	else
		return (get_prop2(data, list, stop, tabi));
	free_comp(data);
	if (prop == NULL)
		return (NULL);
	return (get_args(prop, 1, get_high_len(prop), list));
}
