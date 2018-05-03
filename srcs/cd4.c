/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:44:17 by mallard           #+#    #+#             */
/*   Updated: 2018/05/04 01:53:42 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

void		cd_link(t_env **env, char *cd, char *buf, char *real)
{
	char		*b;
	char		*cd2;

	cd2 = ft_strdup(cd);
	if (chdir(cd) == 0)
	{
		b_export((b = ft_strjoin("OLDPWD=", buf)), &(*env));
		free(b);
		b_export((b = ft_strjoin("PWD=", cd2)), &(*env));
		free(b);
	}
	else
	{
		if (access(cd, F_OK) == 0)
			ft_putstr_fd("cd: permission denied: ", 2);
		else
			ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(real, 2);
	}
	free(cd2);
}

int			usage(void)
{
	ft_putendl_fd("usage: cd [-LP] [path...]", 2);
	return (2);
}

int			check_flags(char **cd, int *tab1)
{
	int		a;

	a = 0;
	if (!cd[0] || ((!ft_strcmp(cd[0], "-")
		|| !ft_strcmp(cd[0], "~")) && !cd[1]))
		return (0);
	while (cd[tab1[0]] && cd[tab1[0]][0] == '-')
	{
		while (cd[tab1[0]][a])
		{
			if ((cd[tab1[0]][a] != '-' && cd[tab1[0]][a] != 'P' &&
				cd[tab1[0]][a] != 'L') || (cd[tab1[0]][a] == '-'
				&& cd[tab1[0]][a + 1] == '-'))
				return (usage());
			a++;
		}
		a = 0;
		tab1[0]++;
	}
	if (!cd[tab1[0]] || cd[tab1[0] + 1])
		return (usage());
	if (tab1[0] > 0 && cd[tab1[0] - 1][ft_strlen(cd[tab1[0] - 1]) - 1] == 'P')
		return (1);
	return (0);
}

char		*ft_getenv(t_env *env)
{
	while (env && ft_strcmp(env->name, "PWD="))
		env = env->next;
	if (env && !ft_strcmp(env->name, "PWD="))
		return (ft_strdup(env->ctn));
	return (NULL);
}

char		*ft_strndup(char *s, int len)
{
	char	*result;
	int		i;

	i = 0;
	len = (size_t)len;
	if (ft_strlen(s) < (size_t)len)
		len = ft_strlen(s);
	if (!(result = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
