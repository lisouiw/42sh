/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:51:13 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:51:15 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

t_glob	*glob_add_nul(t_glob *gp)
{
	t_glob	*new;
	t_glob	*tmp;

	tmp = gp;
	gp = glob_ascii(gp);
	if (!(new = (t_glob*)malloc(sizeof(t_glob))))
		return (NULL);
	new->cmd = NULL;
	new->i[0] = 0;
	new->i[1] = 2;
	new->prev = NULL;
	new->next = NULL;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->prev = tmp;
	tmp->next = new;
	return (gp);
}

t_glob	*glob_path_list(t_glob *g, char *s, int i)
{
	DIR				*d;
	struct dirent	*dir;

	g = NULL;
	if ((d = opendir(s)) == NULL)
		return (NULL);
	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] != '.')
			g = glob_list(g, strjoin_free_n(ft_strjoin(s, "/"),
				dir->d_name, 1), i);
	}
	closedir(d);
	if (g != NULL)
		g = glob_add_nul(g);
	return (g);
}

t_glob	*glob_list(t_glob *g, char *s, int i)
{
	t_glob	*new;
	t_glob	*tmp;

	tmp = g;
	if (!(new = (t_glob*)malloc(sizeof(t_glob))))
		return (NULL);
	new->cmd = s;
	new->i[0] = i;
	new->i[1] = 1;
	new->prev = NULL;
	new->next = NULL;
	if (g == NULL)
		return (new);
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
	return (g);
}

t_glob	*star_simple_list(t_glob *g)
{
	DIR				*d;
	struct dirent	*dir;

	if ((d = opendir(".")) == NULL)
		return (NULL);
	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] != '.')
			g = glob_list(g, ft_strdup(dir->d_name), 0);
	}
	closedir(d);
	return (g = glob_add_nul(g));
}

t_glob	*star_hide_list(t_glob *g)
{
	DIR				*d;
	struct dirent	*dir;

	if ((d = opendir(".")) == NULL)
		return (NULL);
	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] == '.')
			g = glob_list(g, ft_strdup(dir->d_name), 0);
	}
	closedir(d);
	return (g = glob_add_nul(g));
}
