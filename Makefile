# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mallard <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/03 11:37:12 by mallard           #+#    #+#              #
#    Updated: 2018/05/04 03:20:53 by mallard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

CC = gcc

SRCDIR = srcs

FLAGS = -Wall -Werror -Wextra -g

SRCS =  main.c term.c ed.c env.c touch.c print_shell.c treatmt.c exec.c ctrl.c \
		tools.c init.c parsing.c prompt.c giv_str.c pascutcopy.c signal.c \
		parsing_type.c parsing_type_fct.c parsing_tools.c free.c exec_tools.c \
		pipe.c redirecting.c redirecting_checking.c heredoc.c error.c \
		aggregation.c env2.c treatmt_here.c separate_cmd.c free2.c init2.c \
		join.c	parse_synthaxe.c tools2.c free_cut.c histo.c add_doc_delim.c \
		translate.c sub_check_quotes.c sub_calculator.c sub_op.c \
		parsing_backslash.c sub_tools.c glob.c glob_algo.c glob_fct.c \
		glob_fct_brackets.c glob_fct_star.c glob_free.c glob_list.c \
		glob_list_ascii.c glob_list_p_inter.c glob_tab.c glob_tab_add.c \
		glob_tab_add2.c glob_tools.c glob_brace.c glob_brace_parsing.c \
		glob_brace_semicolon_split.c glob_brace_split.c glob_brace_two_comas.c \
		glob_brace_parsing_check.c sub_check_quotes_2.c cd.c cd2.c cd3.c cd4.c \
		cd5.c manage_env.c ft_echo.c ft_echo2.c ft_echo3.c ft_exit.c \
		sub_trad_d.c sub_check_calc.c sub_set_op.c sub_translate.c \
		auto_begin_comp.c auto_core_comp.c auto_display.c auto_display2.c \
		auto_end.c auto_get_prop.c auto_parse_comp.c auto_tool_comp.c \
		auto_tool2_comp.c auto_tool3_comp.c auto_tool4_comp.c \
		
SRC_N = $(addprefix $(SRCDIR)/, $(SRCS))

OBJDIR = objs

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFT= -L./libft/ -lft

all : $(NAME)

$(NAME): $(OBJS)
	make -C ./libft/
	$(CC) $(OBJS) $(LIBFT) $(FLAGS) -o $(NAME) -ltermcap -g

sanitize: $(OBJS)
	make -C ./libft/
	$(CC) $(OBJS) $(LIBFT) $(FLAGS) -fsanitize=address -o $(NAME) -ltermcap -g

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
