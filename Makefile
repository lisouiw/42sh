NAME = 42sh

CC = gcc

SRCDIR = srcs

FLAGS = -Wall -Werror -Wextra -g

GLOB = glob.c glob_algo.c glob_fct.c glob_fct_brackets.c glob_fct_star.c glob_free.c glob_list.c glob_list_ascii.c glob_list_p_inter.c glob_tab.c glob_tab_add.c glob_tab_add2.c glob_tools.c

SRCS =  main.c term.c ed.c env.c touch.c print_shell.c treatmt.c exec.c ctrl.c \
		tools.c init.c parsing.c prompt.c giv_str.c pascutcopy.c signal.c \
		parsing_type.c parsing_type_fct.c parsing_tools.c free.c exec_tools.c \
		pipe.c redirecting.c redirecting_checking.c cd.c heredoc.c error.c \
		aggregation.c env2.c treatmt_here.c separate_cmd.c free2.c init2.c \
		join.c	parse_synthaxe.c tools2.c free_cut.c histo.c add_doc_delim.c \
		print_outils.c translate.c sub_check_quotes.c sub_calculator.c \
		sub_op.c parsing_backslash.c sub_tools.c $(GLOB) sub_check_quotes_2.c \
		sub_trad_d.c sub_check_calc.c sub_set_op.c sub_translate.c

SRC_N = $(addprefix $(SRCDIR)/, $(SRCS))

OBJDIR = objs

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFT= -L./libft/ -lft

all : $(NAME)

$(NAME): $(OBJS)
	make -C ./libft/
	$(CC) $(OBJS) $(LIBFT) $(FLAGS) -o $(NAME) -ltermcap -g

${OBJDIR}/%.o: srcs/%.c
	@mkdir -p ${OBJDIR}
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	make -C ./libft/ clean
	/bin/rm -rf $(OBJDIR)

fclean: clean
	make -C ./libft/ fclean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
