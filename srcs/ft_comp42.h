/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comp42.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 18:14:10 by paoroste          #+#    #+#             */
/*   Updated: 2018/05/01 16:01:04 by ltran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMP42_H
# define FT_COMP42_H
# include "../twenty.h"
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

typedef struct			s_stop
{
	int					stop;
	char				*print;
	int					cut;
	int					nb;
	int					add;
	struct s_comp		*data;
	int					more;
}						t_stop;

typedef struct			s_data
{
	char				*arg;
	int					cursor;
	struct s_data		*next;
	struct s_data		*prev;
	int					max_len;
	int					how_col;
	int					how_prop;
	int					how_row;
	int					nb;
}						t_data;

typedef struct			s_comp
{
	char				*path;
	char				**cmd;
	int					all_prop;
	int					nb;
	char				**in_path;
	char				*str;
	DIR					*rep;
	struct dirent		*file;
	char				*d_name;
	int					i;
	char				*find;
}						t_comp;

t_data					*g_se;
t_stop					*g_se2;

t_stop					*core_comp42(char *str, t_data *list, t_stop *stop,
		int *tabi);
void					ft_comp42(int nb, char *str, t_stop *list);

void					ft_set_term(int i, int nb);
void					ft_move(void);
void					s_winch(int i);

int						out_size(t_data *list);
void					out_clean(void);
void					free_data(t_data *list);
void					free_comp(t_comp *data);
void					free_stop(t_stop *stop);

void					stop_init(t_stop *stop, char *str, int i);
void					data_init(t_comp *data);
char					**init_path(void);

t_data					*check_command(t_data *list, t_stop *stop);
void					print_list(t_data *list, int x, int y);
void					final_print(t_data *list, t_stop *stop);

void					ft_up(t_data *list, int col, int prop, int i);
void					ft_down(t_data *list, int col, int prop, int i);
void					ft_right(t_data *list);
void					ft_left(t_data *list);

char					*strdupmore(char *src, int nb);
int						get_high_len(char **proposition);
t_data					*do_prev(t_data *list, t_data *tmp);
char					*epur_str(char *str);
int						where_am_i(char *str, int i);
int						do_space(char *command);
int						how_cut(char *str, int i, int len);
char					*to_str(char **cmd);
char					*add_str(char *str, int i);
char					*add_home(char *str);
int						no_bin(char *str);
int						cursor_midspace(char *str, int i);

char					**parse_select(char *str, int i, char **path,
		t_stop *stop);
char					*get_occur(char *cmd, int what, int i, int repere);
char					*get_path(t_comp *data, int i, int path, int *tabi);
char					*find(char *str, int *tb, char *tmp, char *neww);
char					*get_path2(t_comp *data, int i, int path, int *tabi);
char					*cut_path(char *str);

t_data					*get_prop(char *str, t_stop *stop, t_data *list,
		int *tb);
t_data					*get_args(char **av, int i, int nb, t_data *list);
t_data					*get_prop2(t_comp *data, t_data *list, t_stop *stop,
		int *tb);
char					**get_prop2_2(t_comp *data, int i, char **prop,
		DIR *rep);
char					**prop_2_2(struct dirent *file, t_comp *data,
		char **prop, DIR *rep);
t_data					*get_prop_rac(t_comp *data, t_data *list, t_stop *stop,
		int *tb);
char					**prop_2(t_comp *data, struct dirent *file, int i,
		DIR *rep);
char					**prop_rac(char *path, struct dirent *file, DIR *rep,
		int nb);

#endif
