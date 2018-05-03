/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:44:01 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:44:02 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

static char	*delete_dot3(char *cd, char *pwd, int a, char *tmp)
{
	tmp = ft_strndup(&cd[a], check_next_cd(&cd[a]));
	if (pwd[ft_strlen(pwd) - 1] != '/')
		pwd = ft_strjoin_free(pwd, "/", 1);
	pwd = ft_strjoin_free(pwd, tmp, 3);
	if (pwd)
		pwd = purification(pwd, 0);
	return (pwd);
}

static int	delete_dot4(char *cd, int a)
{
	if (cd[a] == '.')
		a++;
	if (cd[a] == '.')
		a++;
	if (cd[a] == '/')
		a++;
	return (a);
}

static char	*delete_dot2(char *cd, char *pwd, int a, char *tmp)
{
	int i;

	while (cd[a])
	{
		i = ft_strlen(pwd) - 1;
		while (cd[a] && cd[a + 1] && cd[a] == '.' && cd[a + 1] == '.')
		{
			if (pwd[i] == '/' && i > 1)
			{
				pwd[i] = '\0';
				i--;
			}
			while (i > 1 && pwd[i] != '/')
				i--;
			a = delete_dot4(cd, a);
			pwd[i] = '\0';
		}
		if (check_next_cd(&cd[a]))
			pwd = delete_dot3(cd, pwd, a, tmp);
		a = check_next_cd(&cd[a]) + a;
	}
	return (pwd);
}

char		*delete_dot(char *cd, t_env **env, int a)
{
	char		*pwd;
	char		*tmp;

	tmp = NULL;
	if ((cd[0] == '/') || ((pwd = ft_getenv(*env)) == NULL))
		return (cd);
	if (cd[0] != '/' && cd[0] != '.' && cd[1] && cd[1] != '.')
	{
		tmp = ft_strdup("/");
		cd = ft_strjoin_free(tmp, cd, 3);
	}
	if (pwd[0] == '/' && pwd[1] == '\0')
		cd = purif2(cd);
	cd = purif3(cd);
	pwd = delete_dot2(cd, pwd, a, tmp);
	if (pwd)
		pwd = purification(pwd, 1);
	free(cd);
	if (pwd[0] == '\0')
	{
		free(pwd);
		return (ft_strdup("/"));
	}
	else
		return (pwd);
}
