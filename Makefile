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
CFLAGS				= -g  -Iinclude -Ilibft/include -Wall -Wextra -Werror -Wpedantic
LD					= clang
LD_FLAGS			= -g -Llibft -lft

TARGET				= minishell


# SOURCES


SRCS				= $(addprefix src/, main.c parsecl.c)

OBJS				= $(SRCS:%.c=%.o)

# RULES

all: $(TARGET)

libft:
	git clone https://github.com/aurelien-brabant/libft

$(TARGET): libft libft/libft.a $(HEADERS) $(OBJS) 
	$(LD) -o $(TARGET) $(OBJS) $(LD_FLAGS)

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
	@printf "[\033[1;36mminishell\033[0;m] \033[1;37mCC \033[0;32m$<\033[0m\n"
