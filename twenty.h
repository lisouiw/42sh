/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twenty.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltran <ltran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 11:37:22 by mallard           #+#    #+#             */
/*   Updated: 2018/05/04 04:25:25 by mallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTY_H
# define TWENTY_H

# include "libft/libft.h"
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct		s_glob
{
	char			*cmd;
	size_t			i[2];
	struct s_glob	*prev;
	struct s_glob	*next;
}					t_glob;

typedef struct		s_glob_p
{
	char			*cmd;
	size_t			i[2];
	struct s_glob_p	*prev;
	struct s_glob_p	*next;
}					t_glob_p;

typedef struct		s_glob_i
{
	int				deb;
	int				end;
}					t_glob_i;

typedef struct		s_glob_b
{
	int				deb;
	int				end;
	char			*s;
	char			*m;
	char			*e;
	char			*cs;
	char			*ce;
	char			*cms1;
	char			*cms2;
}					t_glob_b;

typedef struct		s_op
{
	long			x;
	int				priority;
	char			op;
	struct s_op		*next;
}					t_op;

typedef struct		s_num
{
	int				tb[3];
}					t_num;

typedef struct		s_here
{
	char			*delim;
	char			*doc;
	int				ok[2];
	struct s_here	*next;
	struct s_here	*prev;
}					t_here;

typedef struct		s_froz
{
	int				mode[4];
	char			buf[3];
	char			*paste;
	char			*cmd;
	int				nb[1];
	struct s_here	*here;
}					t_froz;

typedef struct		s_env
{
	char			*name;
	char			*ctn;
	struct s_env	*next;
}					t_env;

typedef struct		s_edit
{
	int				rpz[5];
	char			c[1];
	struct s_edit	*next;
	struct s_edit	*prev;
}					t_edit;

typedef struct		s_his
{
	char			*cmd;
	struct s_his	*next;
	struct s_his	*prev;
}					t_his;

typedef struct		s_cmd
{
	char			*cmd;
	int				type;
	int				start;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct		s_exec
{
	int				p[2];
	int				in;
	int				out;
	int				err;
	int				cmd;
	int				pipe;
	int				fd;
}					t_exec;

typedef struct		s_glob_a
{
	int				deb;
	int				end;
	char			*s;
	char			*m;
	char			*e;
	char			*cs;
	char			*ce;
	char			*cms1;
	char			*cms2;
	int				*ok;
	struct s_glob_a	*next;
}					t_glob_a;

typedef struct		s_proc
{
	pid_t			pid;
	struct s_proc	*next;
}					t_proc;

typedef struct		s_varq
{
	char			*cmd;
	struct s_varq	*next;
}					t_varq;

typedef struct		s_stop
{
	int				stop;
	char			*print;
	int				cut;
	int				nb;
	int				add;
	struct s_comp	*data;
	int				more;
	int				sig;
}					t_stop;

typedef struct		s_data
{
	char			*arg;
	int				cursor;
	struct s_data	*next;
	struct s_data	*prev;
	int				max_len;
	int				how_col;
	int				how_prop;
	int				how_row;
	int				nb;
}					t_data;

typedef struct		s_comp
{
	char			*path;
	char			**cmd;
	int				all_prop;
	int				nb;
	char			**in_path;
	char			*str;
	DIR				*rep;
	struct dirent	*file;
	char			*d_name;
	int				i;
	char			*find;
}					t_comp;

int					g_ok;
int					g_kill;
struct s_num		*g_nb;
struct s_env		*g_env;
struct s_his		*g_hs;
struct s_froz		*g_fz;
struct s_edit		*g_ed;

int					add_delim(t_froz *g_fz, t_cmd *ex);
void				add_doc_s(t_froz *g_fz, char *s);
int					add_doc(t_froz *g_fz, char *s);
void				aggregation_out(char **t);
void				aggregation_in(char **t);
void				cd_prev(t_env **env, char *buf);
void				cd_name(t_env **env, char *cd, char *user, char *buf);
void				cd_simple(t_env **env, char *cd, char *buf, char *real);
void				b_cd(char **cd, t_env **env, int a);
void				ctrl_touch(t_edit **ed, t_froz **g_fz, char c, t_env *env);
t_edit				*home_end(t_edit *ed, t_froz *g_fz);
t_edit				*up_down(t_edit *ed, char c);
t_edit				*move_word_right(t_edit *ed);
t_edit				*move_word_left(t_edit *ed);
void				modif_ed_nw(t_edit **ed, t_edit **nw);
void				modif_edit(t_edit **ed, t_edit **nw);
t_edit				*add_ed(t_edit *ed, char c, t_edit *nw, t_froz **g_fz);
t_edit				*init_edit(t_edit *init);
t_edit				*erase_ed(t_edit *ed);
void				b_setenv(char **cut, t_env *env);
void				b_export(char *cut, t_env **env);
void				b_unset(char **cut, t_env **env, int i);
t_env				*add_env(char *environ, t_env *env, size_t one, size_t all);
t_env				*give_env(t_env *env);
void				lst_add_tenv(t_env **alst, t_env *new);
t_env				*t_env_tmp(t_env *env);
int					env_flags_check(char **cut);
void				set_new_env(char **cut, t_env *env, t_exec *s);
void				builtin_env(char **cut, t_env *env, t_exec *s);
int					error_syntax(t_froz *g_fz);
int					give_path(t_env *env, char **cut, int i, char **tab_env);
char				**list_to_tab(t_env *env, char **tab_env);
void				print_tab(char **ta, int i);
t_env				*exec_fct_nf(char **cut, t_env *env, t_cmd **ex, t_exec *s);
void				b_other(char **cut, t_env *env);
void				b_other_nf(char **cut, t_env *env, t_exec *s);
int					give_path_nf(t_env *env, char **cut, int i, char **tab_env);
void				free_cut1(t_edit **ed, t_edit *tmp);
void				free_cut(t_edit **ed, t_froz *g_fz);
void				free_all_ex(t_cmd **ex);
void				free_init_g_fz(t_froz *g_fz);
void				free_for_hs(void);
void				free_for_exit(char *cmd, int i);
void				free_elem(t_env *tmp);
void				free_ed(t_edit **ed, t_froz *g_fz);
void				free_list(t_env **env);
char				*t_strjoin(char *f, char *s, char *t);
void				free_tab(char **array);
char				*ed_str(t_edit *cmd, char *s, int nb);
char				*join_cmd_nw(char *cmd, t_edit *ed, t_froz *g_fz);
char				*join_cmd(char *cmd, t_edit *ed, t_froz *g_fz);
void				malloc_here(t_froz *g_fz);
void				add_here_struct(t_froz *g_fz, char *s);
int					check_struct(t_froz *g_fz);
void				histo_add(t_his *hs, t_edit **ed, t_froz **g_fz);
t_his				*histo(t_his *hs, char c, t_edit **ed, t_froz **g_fz);
t_his				*init_hs(t_his *hs, t_his *next);
t_num				*init_shell(t_froz **g_fz, t_env **env, t_edit **ed,
					t_his **hs);
t_froz				*init_g_fz(t_froz *g_fz);
void				init_data(t_froz **g_fz);
void				init_for_new(t_his **hs, t_froz **g_fz, t_edit **ed);
t_cmd				*init_ex(t_cmd *ex);
void				init_launch(t_exec *dot, t_cmd **ex);
void				join_ex(t_cmd **ex);
void				join_redirecting2(t_cmd **join, t_cmd **ex);
void				join_redirecting(t_cmd **ex);
void				cursor_end(t_edit *ed);
void				put_my_cur(int nb, char c);
int					parse_synthaxe_1(t_cmd *ex);
void				parse_synthaxe_2(t_cmd *ex);
int					parse_synthaxe(t_cmd *ex, char *s);
int					isnumber(char *s);
int					isnumber_len(char *s);
t_cmd				*parse_redirec(t_cmd *ex, char *s);
t_cmd				*parse_ampersand(t_cmd *ex);
t_cmd				*parse_great_than(t_cmd *ex, char *s);
t_cmd				*parse_less_than(t_cmd *ex, char *s);
t_cmd				*parse_pipe_or(t_cmd *ex);
t_cmd				*giv_type(t_cmd *ex, char *s);
t_cmd				*parse_op_int(t_cmd *ex, char *s);
int					parse_type(t_cmd **ex);
char				*replace_nwl_spc(char *s);
int					parsing_op(char *s, t_cmd **ex, t_froz *g_fz);
int					parsing_quote(char *s);
int					parsing(t_edit *ed, t_froz *g_fz, t_cmd **ex);
t_edit				*paste(t_edit *ed, t_froz **g_fz);
t_edit				*copy(t_edit *ed, t_froz **g_fz);
void				cut(t_edit **ed, t_froz **g_fz);
int					give_paste_in(t_edit **ed);
char				*keep_paste(t_edit **ed, char *s);
void				end_pipe(t_cmd **ex, t_exec **s, int pp);
int					pipe_on(t_cmd *ex);
t_env				*pipe_fct(t_exec *s, t_cmd **ex, t_env *env);
int					ft_put(int c);
void				my_tputs(t_edit *ed, t_froz *g_fz);
void				print_shell(t_edit *ed, t_froz *g_fz);
void				put_cursor(t_edit *ed);
void				save_init(t_edit *ed);
void				put_prompt_init(t_froz **g_fz);
void				put_prompt(t_froz *g_fz);
int					giv_last(t_froz *g_fz);
int					parsing_dup_out(char *s, int n);
int					parsing_dup_in(char *s, int n);
int					redirection_check_create(t_cmd *ex, t_env *env);
void				redirection_file_create(t_cmd *ex, t_env *env);
int					redirection_file_check(t_cmd *ex, t_env *env);
void				redirection(t_cmd **ex, t_env **env, t_exec *s);
void				redirection_fork(t_cmd **ex, t_env **env, t_exec *s);
char				**give_seven(t_cmd *ex, t_env *env);
void				redirecting_exec(t_cmd **ex, t_env **env, char **arr,
					t_exec *s);
void				sub_into_ex_fct(char *s, int i, int in, t_cmd *ex);
t_cmd				*sub_into_ex(char *s, int i, int in, t_cmd *ex);
t_cmd				*separate_cmd_fct(char *s, int *i, int *in, t_cmd *ex);
t_cmd				*separate_cmd(char *s, int i, int in, t_cmd *ex);
void				sig_int(int sig);
void				sig_int3(int sig);
void				sig_int_here_2(void);
void				sig_int_here(int sig);
void				ls_signal(int i);
int					init(void);
int					set_up_term(void);
int					if_only_i(char *s, char c);
int					if_chr_ex(char *s, char c);
int					if_only(char *s, char c);
void				ecriture_info(t_env *lst);
int					white_space(char *s);
char				*strjoin_free(char *nw, char *sub, int i);
char				*strjoin_free_n(char *nw, char *sub, int i);
void				move_on(t_cmd **ex, int i);
t_edit				*touch(t_edit **ed, t_froz **g_fz, t_his **hs, t_env *env);
t_edit				*extern_touch(t_edit *ed, t_froz **g_fz, t_his **hs);
t_edit				*giv_position(t_edit *ed, int i);
t_edit				*left_right(t_edit *ed, t_froz *g_fz);
int					parsing_op_here(char *s, t_cmd **ex, t_froz *g_fz);
int					parsing_here(t_edit *ed, t_froz *g_fz, t_cmd **ex);
t_env				*treat_cmd_here(t_env *env, t_edit **cmd, t_his **hs,
					t_froz **g_fz);
t_env				*treat_cmd(t_env *env, t_edit **cmd, t_his **hs,
					t_froz **g_fz);
void				add_his(t_his **hs, t_his *nw, t_froz *g_fz);
void				redirection_no_cmd(t_cmd **ex, t_env **env, t_exec *s);
t_env				*exec_fct_re(t_cmd **ex, t_env *env, t_exec *s);
t_env				*launchcmd(t_cmd *ex, t_env *env);
t_froz				*init_fz(t_froz *fz);
void				free_init_fz(t_froz *fz);
void				pipe_exec(t_exec **s, t_cmd **ex, t_env *env, int pp);
void				sig_int4(int sig);
void				print_here(t_froz *fz);
void				print_ex(t_cmd *ex);
void				print_ex_up(t_cmd *ex);
int					last_multiple_char(char *s, char c);
int					parse_synthaxe_back(t_cmd *ex);
void				glob(char *s, int *i, t_cmd **ex);
char				*glob_parsing(t_cmd **ex);
char				*join_trad(t_glob *g);
void				init_glob_p(t_glob_p **parse);
int					move_last_star(t_glob_p **parse, t_glob **g);
int					parse_brackets_ok(char *s, int i);
void				brace_int_count(int *a, int b, char *s);
t_glob_p			*add_brace_list(t_glob_p *gp, int *st, int *end, char *s);
t_glob_p			*glob_tab(t_glob_p *gp, char *s);
void				add_start_list_parse(int *a, char *s);
t_glob_p			*add_start_list(t_glob_p *gp, int *st, int *end, char *s);
t_glob				*glob_add_nul(t_glob *gp);
t_glob				*glob_path_list(t_glob *g, char *s, int i);
t_glob				*glob_list(t_glob *g, char *s, int i);
t_glob				*star_simple_list(t_glob *g);
t_glob				*star_hide_list(t_glob *g);
t_glob				*glob_add_inter_prev(t_glob **g, t_glob **gtmp);
t_glob				*glob_add_inter(t_glob *g, t_glob *gtmp);
t_glob_p			*glob_p_add_nul(t_glob_p *gp);
t_glob_p			*glob_p_list(t_glob_p *gp, char *trad);
t_glob				*glob_ascii(t_glob *g);
int					clean_dir_plus(t_glob **g, t_glob_p *parse);
int					clean_dir(t_glob **g, t_glob_p *parse);
int					clean_str(t_glob **g, t_glob_p *parse);
int					clean_char(t_glob **g, t_glob_p **parse);
int					check_question(char *cmd, char *s, int i, char *next);
int					clean_brackets_star_loop(t_glob **g, char **tb, int y,
					int i);
int					clean_brackets_star(t_glob **g, t_glob_p **parse);
int					clean_str_star_check(t_glob **g, t_glob_p *parse, size_t i);
int					clean_str_star(t_glob **g, t_glob_p *parse);
int					clean_star_loop(t_glob_p **parse, t_glob **g);
int					clean_star(t_glob_p **parse, t_glob **g);
size_t				count_brace(char *s);
char				**split_bracket(char *s);
int					clean_brackets(t_glob **g, t_glob_p **parse);
int					glob_cleaning(t_glob_p **parse, t_glob **g);
int					glob_parsing_clean(t_glob **g, t_glob_p *parse);
t_glob				**glob_parsing_p(t_glob **g, t_glob_p *parse, int a);
void				translate_glob(t_glob **g, char *s, t_glob_i y, t_cmd **ex);
t_glob_p			*check_backslash_str(t_glob_p *gp, int *st, int *end,
					char *trad);
t_glob_p			*check_match_str(t_glob_p *gp, int *st, int *end,
					char *trad);
t_glob_p			*add_question_list(t_glob_p *gp, int *st, int *end,\
					char *s);
void				glob_free1(t_glob *g);
void				glob_free(t_glob *g);
void				glob_free_list(t_glob *g);
void				glob_p_free_list(t_glob_p *g);
int					check_op(char tmp[3], int *error);
int					check_var(char *var, int *error, int op, int i);
long				operator(long a, long b, char op);
int					check_list(t_op **op);
int					check_long(char *str);
void				set_op(char c, int *vip);
int					add_op(t_op **op, char *tmp, int *i, int vip);
int					bracket(char *var);
t_op				*op_list(char *var, int vip, int i);
int					op_priority(t_op *op, int priority);
t_op				*cal2(t_op *op, char *var);
t_op				*calculator(char *var);
void				error_op(int error, char *var, t_op *op);
int					check_quote(char *cmd, char c, int i);
char				*charsub(char *var, char **cmd, int i, int j);
int					expand_var_env(char **cmd, int i, t_env *env);
int					loopy_loop(char **str, t_env *env);
t_op				*op_new(long x, char op, int priority);
void				op_add(t_op **op, t_op *new);
int					check_priority(t_op *op);
void				free_op(t_op **op);
long				ft_atol(const char *str);
int					ft_isop(int c);
int					ft_isnumber(int c);
int					ft_space(int c);
int					ft_isvip(char c);
int					trad_d(t_env *env, char **cmd, int i, char c);
int					ft_var_end(char c);
char				*find_variable(char *var, t_env *env);
char				*get_var(char *str, char c, int *j, int i);
char				**translate(t_env *env, t_cmd **ex);
void				ft_replace_b(char *str, int i);
int					ft_isquote(char c);
int					arg_nbr(char *cmd);
char				*delete_dot(char *cd, t_env **env, int a);
void				free_b_cd(char *real, char *cd, char *way);
char				*purif2(char *str);
char				*purif3(char *str);
char				*purification(char *str, int ind);
int					check_next_cd(char *str);
char				*ft_strndup(char *s, int len);
char				*ft_getenv(t_env *env);
int					check_flags(char **cd, int *tab1);
int					usage(void);
void				cd_link(t_env **env, char *cd, char *buf, char *real);
void				cd_simple(t_env **env, char *cd, char *buf, char *real);
void				cd_prev(t_env **env, char *buf);
void				cd_home(t_env **env, char *buf, char *b);
void				cd_name(t_env **env, char *cd, char *user, char *buf);
void				print_octal(int nb);
int					check_octal3(char *str, int i, char **ta, int *t);
int					check_octal2(char *str, int i, char **ta, int *t);
int					check_octal42(char **ta, int *t, int i, char *str_nb);
int					check_octal(char **ta, int *t, int i);
int					check_echo_flags2(char **cd, int *tab1, int a, int b);
int					check_echo_flags(char **cd, int *tab1, int a, int b);
int					check_n(char **ta, int *t, int a);
void				ft_exit(char *cmd);
void				manage_env(t_env *env);
char				*semicolon_translate(t_glob_b *b, char *final);
char				*join_semicolon(t_glob_b *b);
char				*join_two_comas(t_glob_b *b);
char				*glob_brace_str(t_cmd **ex, t_glob_b *b);
char				*glob_brace(t_cmd **ex);
char				*join_two_comas_num_down(t_glob_b *b, int num1, int num2);
char				*join_two_comas_num_up(t_glob_b *b, int num1, int num2);
char				*join_brace_nf(t_glob_b *b, char *final);
char				*join_two_comas_alpha_down(t_glob_b *b);
char				*join_two_comas_alpha_up(t_glob_b *b);
char				*modif_s_e(t_glob_b *b, char *final);
char				*giv_brace_e(char *s);
char				*giv_brace_s(char *s);
char				*join_brace(t_glob_b *b, char *final);
int					int_split(char *mid, int *i);
void				free_glob_a(t_glob_a *a);
t_glob_a			*add_glob_a(char *mid, t_glob_a *a);
t_glob_a			*give_semicolon_list(char *mid, t_glob_b *b, t_glob_a *a);
char				*join_list_glob_a(t_glob_a *a);
int					check_brace(char *s, t_glob_b *b);
int					match_brace(char *s, t_glob_b *b, int i);
int					glob_brace_int(t_cmd **ex, t_glob_b *b);
int					isaltwo(char *deb, char *end);
int					brace_semicolon(char *s);
int					brace_two_comas(t_glob_b *b);
char				*modif_s_e(t_glob_b *b, char *final);
char				*giv_brace_e(char *s);
char				*giv_brace_s(char *s);
int					isaltwo(char *deb, char *end);
int					brace_semicolon(char *s);
int					isnumber_np(char *s);
void				ft_home(char **cmd, int i, t_env *env);
void				init_free_his(t_his **hs, t_froz **fz, int i, t_cmd **ex);
t_env				*exec_fct_nf_build(char **cut, t_env *env, t_exec *s);
t_env				*exec_fct_build(char **cut, t_env *env, t_exec *s);

t_edit				*auto_completion(t_edit *ed, t_froz *fz, t_env *env);
t_data				*g_se;
t_stop				*g_se2;

t_stop				*core_comp42(char *str, t_data *list, t_stop *stop,
					t_env *env);
void				ft_comp42(int nb, char *str, t_stop *list);

void				ft_set_term(int i, int nb);
void				s_winch(int i);

int					out_size(t_data *list);
void				out_clean(void);
void				free_data(t_data *list);
void				free_comp(t_comp *data);
void				free_stop(t_stop *stop);
t_stop				*ft_set_mssg(t_data *list);

void				stop_init(t_stop *stop, char *str, int i);
void				data_init(t_comp *data);
char				**init_path(void);

t_data				*check_command(t_data *list, t_stop *stop);
t_data				*hey_hook(int buf, t_data *list, t_stop *stop);
void				print_list(t_data *list, int x, int y);
void				final_print(t_data *list, t_stop *stop);

void				ft_up(t_data *list, int col, int prop, int i);
void				ft_down(t_data *list, int col, int prop, int i);
void				ft_right(t_data *list);
void				ft_left(t_data *list);

t_data				*do_prev(t_data *list, t_data *tmp);
int					do_space(char *command);
int					where_am_i(char *str, int i);
char				*to_str(char **cmd);
int					how_cut(char *str, int i, int len);
char				*strdupmore(char *src, int nb);
int					get_high_len(char **proposition);
char				*add_home(char *str, t_env *env);
int					no_bin(char *str);

char				**parse_select(char *str, t_env *env, char **path,
					t_stop *stop);
char				*get_path(t_comp *data, int i, int path, int *tabi);
char				*get_path2(t_comp *data, int i, int path, int *tabi);
char				*find(char *str, int *tb, char *tmp, char *neww);
char				*cut_path(char *str);
char				*epur_str(char *str);

t_data				*get_prop(char *str, t_stop *stop, t_data *list,
					t_env *env);
char				**get_prop22(t_stop *stop, t_comp *data, char **prop,
					int *tb);
t_data				*get_args(char **av, int i, int nb, t_data *list);
t_data				*get_prop2(t_comp *data, t_data *list, t_stop *stop,
					int *tb);
char				**get_prop2_2(t_comp *data, int i, char **prop,
					DIR *rep);
char				**prop_2_2(struct dirent *file, t_comp *data,
					char **prop, DIR *rep);
t_data				*get_prop_rac(t_comp *data, t_data *list, t_stop *stop,
					int *tb);
char				**prop_2(t_comp *data, struct dirent *file, int i,
					DIR *rep);
char				**prop_rac(char *path, struct dirent *file, DIR *rep,
					int nb);
void				build_exit(char **cut, t_env *env, t_cmd **ex);
t_env				*exec_fct(char **cut, t_env *env, t_cmd **ex, t_exec *s);

#endif
