/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:43:53 by mallard           #+#    #+#             */
/*   Updated: 2018/05/04 02:33:37 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

static int	check_dir(char *cd, char *real)
{
	DIR		*di;

	if (!(di = opendir(cd)) && cd[0] != '-' && cd[0] != '~')
	{
		if (access(cd, F_OK) == 0)
			ft_putstr_fd("cd: permission denied: ", 2);
		else
			ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(real, 2);
		free(real);
		free(cd);
		g_ok = 1;
		return (1);
	}
	if (cd[0] != '-' && cd[0] != '~')
		closedir(di);
	return (0);
}

static int	check_home(char **cd2, int *tab1, char *buf, t_env **env)
{
	char	*b;

	b = NULL;
	if ((!(cd2[tab1[0]]) || ft_strcmp(cd2[tab1[0]], "~") == 0))
	{
		cd_home(env, buf, b);
		return (1);
	}
	if ((cd2[tab1[0]] && cd2[tab1[0]][0] && cd2[tab1[0]][0] == '.'
		&& cd2[tab1[0]][1] == '/' && cd2[tab1[0]][2] == '\0')
		|| (cd2[tab1[0]][0] == '.' && cd2[tab1[0]][1] == '\0'))
		return (1);
	return (0);
}

static char	*ini_cd(char **cd2, int *tab1, t_env **env, char *cd)
{
	if (cd2[tab1[0]][0] == '.' && cd2[tab1[0]][1] == '/')
		cd = ft_strdup(&cd2[tab1[0]][2]);
	else
		cd = ft_strdup(cd2[tab1[0]]);
	if ((cd && cd[0] && cd[1]) && ((cd[0] != '-' && cd[0] != '~')
		|| (cd[0] == '.' && cd[1] == '.')))
		if ((cd = delete_dot(cd, env, 0)) == NULL)
			return (NULL);
	return (cd);
}

static int	b_cd2(char *cd, t_env **env, char *buf, char *way)
{
	char	*b;

	b = NULL;
	if (cd && ft_strcmp(cd, "-") == 0)
		cd_prev(env, buf);
	else if ((!(cd) || ft_strcmp(cd, "~") == 0))
		cd_home(env, buf, b);
	else if (cd[0] == '~')
		cd_name(env, cd, NULL, buf);
	else
		cd_link(env, cd[0] == '/' ? cd : way, buf, cd);
	return (1);
}

void		b_cd(char **cd2, t_env **env, int a)
{
	char	buf[PATH_MAX - 1];
	char	*way;
	char	*cd;
	char	*real;
	int		tab1[2];

	tab1[0] = 0;
	cd = NULL;
	getcwd(buf, PATH_MAX);
	a = check_flags(cd2, tab1);
	if (check_home(cd2, tab1, buf, env))
		return ;
	real = ft_strdup(cd2[tab1[0]]);
	if ((cd = ini_cd(cd2, tab1, env, cd)) == NULL)
		return ;
	if (check_dir(cd, real))
		return ;
	way = t_strjoin(buf, "/", cd);
	if (a == 1)
		cd_simple(env, cd[0] == '/' ? cd : way, buf, cd);
	else if (a == 2)
		;
	else if (b_cd2(cd, env, buf, way))
		;
	free_b_cd(real, cd, way);
}
