/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comp42.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:45:46 by mallard           #+#    #+#             */
/*   Updated: 2018/05/03 11:46:18 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMP42_H
# define FT_COMP42_H
# include "twenty.h"
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/ioctl.h>
# include <termcap.h>
# include <dirent.h>
# define IS_SPACE(x) (x == ' ' || x == '\t' || x == '\r' || x == '\f')
# define LEFT		4479771
# define RIGHT		4414235
# define UP			4283163
# define DOWN		4348699
# define TAB		9
# define ENTER		10

#endif
