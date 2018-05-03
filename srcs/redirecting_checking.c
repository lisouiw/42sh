/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting_checking.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:54:19 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:54:20 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../twenty.h"

int		parsing_dup_out(char *s, int n)
{
	size_t	len;
	int		fd;

	if ((len = isnumber_len(s)) + 1 == ft_strlen(s) && s[len] == '-')
	{
		s[len] = '\0';
		if (len > 0)
		{
			dup2(ft_atoi(s), n);
			close(ft_atoi(s));
		}
		else
			close(n);
	}
	else
	{
		fd = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dup2(fd, n);
	}
	return (1);
}

int		parsing_dup_in(char *s, int n)
{
	size_t	len;

	if ((len = isnumber_len(s)) + 1 == ft_strlen(s) && s[len] == '-')
	{
		s[len] = '\0';
		close(ft_atoi(s));
		dup2(n, ft_atoi(s));
		close(ft_atoi(s));
	}
	else
	{
		len = open(s, O_RDONLY);
		dup2(n, len);
	}
	return (1);
}

int		redirection_check_create(t_cmd *ex, t_env *env)
{
	while ((ex)->type >= 6 && (ex)->type <= 11)
	{
		if ((ex)->type == 8 || (ex)->type == 9)
			redirection_file_create(ex, env);
		else if ((ex)->type == 7 && redirection_file_check(ex, env) == 0)
			return (0);
		else if (ex->type == 10)
			aggregation_out(translate(env, &ex));
		else if (ex->type == 11)
			aggregation_in(translate(env, &ex));
		ex = (ex)->next;
	}
	return (1);
}

void	redirection_file_create(t_cmd *ex, t_env *env)
{
	int		nw;
	char	**arr;

	arr = translate(env, &ex);
	if ((ex)->type == 8)
		nw = (arr[2] == NULL) ? open(arr[1], O_CREAT | O_RDWR | O_TRUNC, 0644)
			: open(arr[2], O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		nw = (arr[2] == NULL) ? open(arr[1], O_CREAT | O_RDWR | O_APPEND, 0644)
			: open(arr[2], O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(nw, (arr[2] == NULL ? 1 : ft_atoi(arr[0])));
	free_tab(arr);
	close(nw);
}

int		redirection_file_check(t_cmd *ex, t_env *env)
{
	int		nw;
	char	**arr;

	arr = translate(env, &ex);
	nw = (arr[2] == NULL) ? open(arr[1], O_RDONLY) : open(arr[2], O_RDONLY);
	if (nw == -1)
	{
		ft_putstr_fd("sh: ", 2);
		ft_putstr_fd(((arr[2] == NULL) ? arr[1] : arr[2]), 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_tab(arr);
		return (0);
	}
	close(nw);
	free_tab(arr);
	return (1);
}
