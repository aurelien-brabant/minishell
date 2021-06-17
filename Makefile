
# PROJECT CONFIG

CC					= clang
CFLAGS				= -g  -Iinclude -Ilibft/include -Wall -Wextra -Werror
LD					= clang
LD_FLAGS			= -g -Llibft -lft -lreadline

TARGET				= minishell


# SOURCES


LEXER				= $(addprefix src/lexer/, lexer.c token.c)

PARSER				= $(addprefix src/parser/, parser.c word.c redirection.c	\
					  command.c pipe.c expand.c)

EXEC				= $(addprefix src/exec/, exec.c echo.c cd.c pwd.c export.c	\
				  	unset.c utils.c exit.c fn_exec.c)

SIGNAL				=$(addprefix src/signal/, signal.c)

OTHER				= $(addprefix src/, main.c parse_clopt.c prompt.c error.c	\
				  	minishell.c stat.c argv.c env.c)

SRCS				= $(OTHER) $(LEXER) $(PARSER) $(EXEC) $(SIGNAL)

HEADERS				= $(addprefix include/minishell/, minishell.h constants.h stat.h error.h parser.h lexer.h exec.h signal.h)

OBJS				= $(SRCS:%.c=%.o)

# RULES

all: $(TARGET)

libft:
	git clone https://github.com/aurelien-brabant/libft

$(TARGET): libft $(HEADERS) $(OBJS) 
	make -C libft
	@$(LD) -o $(TARGET) $(OBJS) $(LD_FLAGS)
	@printf "LD\t$(TARGET)\n"

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
	@printf "CC\t$<\n"
