# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/03 11:30:39 by abrabant          #+#    #+#              #
#    Updated: 2021/06/04 12:03:35 by abrabant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# PROJECT CONFIG

CC					= clang
CFLAGS				= -g  -Iinclude -Ilibft/include -Wall -Wextra -Werror 
LD					= clang
LD_FLAGS			= -g -Llibft -lft

TARGET				= minishell


# SOURCES


SRCS				= $(addprefix src/, main.c parse_clopt.c)

HEADERS				= $(addprefix include/minishell/, minishell.h constants.h)

OBJS				= $(SRCS:%.c=%.o)

# RULES

all: $(TARGET)

libft:
	git clone https://github.com/aurelien-brabant/libft

$(TARGET): libft libft/libft.a $(HEADERS) $(OBJS) 
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

libft/libft.a:
	make -C libft

.PHONY: clean fclean re

%.o:%.c $(HEADERS)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "CC\t$<\n"
