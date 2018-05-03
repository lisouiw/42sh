/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_tool2_comp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:43:10 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:43:17 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_comp42.h"

char		*strdupmore(char *src, int nb)
{
	char		*dest;
	char		*str;
	int			i;
	int			diff;

	i = 0;
	diff = nb - ft_strlen(src);
	if (diff == 0)
	{
		dest = strdup(src);
		return (dest);
	}
	str = (char*)malloc(sizeof(char) * (diff + 1));
	dest = strdup(src);
	if (dest == NULL)
		return (NULL);
	while (i < diff)
		str[i++] = ' ';
	str[i] = '\0';
	dest = strjoin_free_n(dest, str, 3);
	return (dest);
}

int			get_high_len(char **proposition)
{
	int			i;
	size_t		nb;
	int			len;

	i = 0;
	nb = 0;
	while (proposition[i])
	{
		if (nb < strlen(proposition[i]))
			nb = strlen(proposition[i]);
		i++;
	}
	len = (int)nb;
	return (len);
}

t_data		*do_prev(t_data *list, t_data *tmp)
{
	t_data		*first;

	first = list;
	while (first->next != tmp)
		first = first->next;
	return (first);
}

char		**prop_2_2(struct dirent *file, t_comp *data, char **prop, DIR *rep)
{
	int			i;

	i = 0;
	while ((file = readdir(rep)) != NULL)
	{
		free(data->d_name);
		data->d_name = ft_strlowcase(file->d_name);
		if (ft_strncmp(data->find, data->d_name,
					ft_strlen(data->find)) == 0)
		{
			prop[i] = strdup(file->d_name);
			if (file->d_type == 4)
				prop[i] = strjoin_free_n(prop[i], "/", 1);
			i++;
		}
	}
	prop[i] = NULL;
	closedir(rep);
	return (prop);
}

char		**get_prop2_2(t_comp *data, int i, char **prop, DIR *rep)
{
	int		nb;

	nb = 0;
	while (data->in_path[i])
	{
		if (!(rep = opendir(data->in_path[i])))
			return (NULL);
		while ((data->file = readdir(rep)) != NULL)
		{
			free(data->d_name);
			data->d_name = ft_strlowcase(data->file->d_name);
			if (ft_strncmp(data->str, data->d_name, ft_strlen(data->str)) == 0)
			{
				prop[nb] = strdup(data->file->d_name);
				if (data->file->d_type == 4)
					prop[nb] = strjoin_free_n(prop[nb], "/", 1);
				nb++;
			}
		}
		closedir(rep);
		i++;
	}
	prop[nb] = NULL;
	return (prop);
}
