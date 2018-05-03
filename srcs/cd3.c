/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:44:09 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:44:11 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		check_next_cd(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '/')
		i++;
	if (str[i] == '.' && str[i] == '/')
		return (i + 2);
	while (str[i] && str[i] != '/')
		i++;
	if (str[i] == '/')
		i++;
	return (i);
}

char	*purification(char *str, int ind)
{
	char	*final;
	int		i;
	int		a;

	i = 0;
	a = 0;
	final = ft_memalloc(ft_strlen(str));
	while (str[i] != '\0')
	{
		if (str[i] && str[i + 1] && str[i] == '/' && str[i + 1] == '/')
			i++;
		final[a] = str[i];
		a++;
		i++;
	}
	if (final[ft_strlen(final) - 1] == '/' &&
		final[ft_strlen(final)] > 1 && ind == 1)
		final[ft_strlen(final) - 1] = '\0';
	final[a] = '\0';
	free(str);
	return (final);
}

char	*purif3(char *str)
{
	char	*final;
	int		i;
	int		a;

	i = 0;
	a = 0;
	final = ft_memalloc(ft_strlen(str));
	while (str[i] != '\0')
	{
		while (str[i] && str[i + 1] && str[i] == '.' && str[i + 1] == '/'
			&& i > 0 && str[i - 1] != '.')
			i = i + 2;
		final[a] = str[i];
		a++;
		i++;
	}
	final[a] = '\0';
	free(str);
	return (final);
}

char	*purif2(char *str)
{
	char	*final;
	int		i;
	int		a;

	i = 0;
	a = 0;
	final = ft_memalloc(ft_strlen(str));
	if (str[0] && str[1] && str[0] == '/')
		i++;
	while (str[i])
	{
		final[a] = str[i];
		a++;
		i++;
	}
	if (final[ft_strlen(final) - 1] == '/' && final[ft_strlen(final)] > 1)
		final[ft_strlen(final) - 1] = '\0';
	free(str);
	return (final);
}

void	free_b_cd(char *real, char *cd, char *way)
{
	free(real);
	free(cd);
	free(way);
}
