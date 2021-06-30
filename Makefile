
# PROJECT CONFIG

CC					= clang
CFLAGS				= -g  -Iinclude -Ilibft/include -Wall -Wextra -Werror
LD					= clang
LD_FLAGS			= -g -Llibft -lft -lreadline

TARGET				= minishell


# SOURCES


LEXER				= $(addprefix src/lexer/, lexer.c token.c utils.c)

PARSER				= $(addprefix src/parser/, parser.c word.c operator.c expand.c)

BUILTIN				= $(addprefix src/builtin/, builtin.c echo.c cd.c pwd.c export.c unset.c exit.c env.c)

EXEC				= $(addprefix src/exec/, exec.c redirection.c utils.c fork.c)

SIGNAL				=$(addprefix src/signal/, signal.c)

DATASTRUCTURE		= $(addprefix src/datastructure/, redirv.c pipeline.c stringv.c)

OTHER				= $(addprefix src/, main.c parse_clopt.c prompt.c error.c	\
				  	minishell.c env.c heredoc.c)

SRCS				= $(OTHER) $(LEXER) $(PARSER) $(SIGNAL) $(BUILTIN) $(DATASTRUCTURE) $(EXEC)

HEADERS				= $(addprefix include/minishell/, minishell.h constants.h error.h parser.h lexer.h exec.h signal.h datastructure.h)

OBJS				= $(SRCS:%.c=%.o)

# RULES

all: $(TARGET)

libft:
	git clone https://github.com/aurelien-brabant/libft

$(TARGET): libft $(HEADERS) $(OBJS) 
	@. ./configure.sh
	@make --silent -C libft
	@$(LD) -o $(TARGET) $(OBJS) $(LD_FLAGS)
	@printf "\033[1;38mLD\t\033[1;32m$(TARGET)\n"

norm:
	@norminette src
	@norminette include

clean:
	@$(RM) $(OBJS) 

fclean: clean
	@$(RM) $(TARGET)

re: fclean all

# Compile libft

.PHONY: clean fclean re

%.o:%.c $(HEADERS)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "\033[1;38mCC\t\033[0m$<\n"
