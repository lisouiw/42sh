/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paoroste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 11:05:17 by paoroste          #+#    #+#             */
/*   Updated: 2018/04/25 18:46:44 by paoroste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_comp42.h"

char			**prop22(t_comp *data, struct dirent *file, DIR *rep, int nb)
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

t_data			*get_prop2(t_comp *data, int i, t_data *list)
{
	char		**prop;

	prop = prop22(data, NULL, NULL, 0);
	if (prop == NULL)
		return (NULL);
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

t_data			*get_prop(char *str, t_stop *stop, t_data *list, int *tb)
{
	t_comp		*data;
	char		**prop;

	data = (t_comp*)malloc(sizeof(t_comp));
	data->cmd = parse_select(str, 0, NULL, stop);
	data_init(data);
	if ((data->cmd[0] && data->cmd[1]))
	{
		(data->cmd[1][0] != ' ') ? stop->cut = 1 : 0;
		(data->cmd[1][0] != ' ') ? data->nb = stop->nb : 0;
		data->path = get_path(data, 0, 0, tb);
		if (data->all_prop == 1)
			prop = prop_rac(data->path, NULL, NULL, 0);
		else
			prop = prop_2(data, NULL, 0, NULL);
	}
	else
		return (get_prop2(data, 0, list));
	free_comp(data);
	if (prop == NULL)
		return (NULL);
	return (get_args(prop, 1, get_high_len(prop), list));
}
