
NAME = 42sh

CC = gcc

SRCDIR = srcs

FLAGS = -Wall -Werror -Wextra -g

SRCS =  main.c term.c ed.c env.c touch.c print_shell.c treatmt.c exec.c \
ctrl.c tools.c init.c parsing.c prompt.c giv_str.c pascutcopy.c \
parsing_type.c parsing_type_fct.c parsing_tools.c free.c \
exec_tools.c pipe.c redirecting.c redirecting_checking.c \
signal.c cd.c heredoc.c aggregation.c \
error.c env2.c treatmt_here.c separate_cmd.c free2.c init2.c \
join.c	parse_synthaxe.c tools2.c free_cut.c histo.c \
add_doc_delim.c print_outils.c

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
