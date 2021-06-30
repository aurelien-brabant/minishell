# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/30 15:22:25 by abrabant          #+#    #+#              #
#    Updated: 2021/06/27 00:26:04 by abrabant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ~~~~~~~~~~ COMPILATION ~~~~~~~~~~

CC						= clang

CFLAGS					= -Wall -Wextra -Werror

INCLUDE_PATH			= ./include/

# ~~~~~~~~~~   PROJECT   ~~~~~~~~~~
NAME					= libft.a

# ~~~~~~~~~~   SOURCES   ~~~~~~~~~~

VPATH					= ./src/cstring:./src/ctype:./src/io:./src/io/gnl:	\
						./src/io/printf:									\
						./src/strconv:./src/intconv:./src/unicode:			\
						./src/core:./src/vector:./src/cla:					\
						./src/vector:./src/string:./src/stack:./src/gc

CORE				 	= ft_calloc.c ft_realloc.c ft_bubble_sort.c			\
						ft_clamp.c ft_insertion_sort.c ft_selection_sort.c	\
						ft_gcmp_uint.c ft_gcmp_int.c ft_acmp_int.c			\
						ft_acmp_uint.c ft_quick_sort.c ft_merge_sort.c		\
						ft_get_short_opt.c

CSTRING					= ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strdup.c	\
						ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c	\
						ft_strnstr.c ft_memset.c ft_memcpy.c ft_memccpy.c	\
						ft_memmove.c ft_memcmp.c ft_memchr.c ft_substr.c	\
						ft_split.c ft_strjoin.c ft_strtrim.c ft_strmapi.c	\
						ft_strrev.c ft_strlwr.c ft_strupr.c ft_strinsrt.c	\
						ft_strcasestr.c ft_strchri.c ft_strhsprfx.c			\
						ft_strhssfx.c ft_strndup.c ft_strcmp.c				\
						ft_strtrim_uniq.c ft_strtok.c ft_strcmpset.c

CTYPE					= ft_isascii.c ft_isdigit.c ft_isalnum.c			\
						ft_isalpha.c ft_isprint.c ft_tolower.c ft_toupper.c	\
						ft_isspace.c ft_islower.c ft_isupper.c

# Special project files for IO

GNL_CORE				= ft_gnl_utils.c

PRINTF_CORE				= parse.c conv_int.c utils.c field_width.c			\
						init_conv.c conv_str.c lenspec.c conv_cur_written.c	\
						buf.c conv_char.c conv_pct.c 						

IO						= ft_putnbr_fd.c ft_putstr_fd.c ft_putchar_fd.c		\
						$(GNL_CORE) ft_gnl.c $(PRINTF_CORE)					\
						ft_printf.c	ft_snprintf.c ft_sprintf.c ft_dprintf.c	\
						ft_vprintf.c ft_vsprintf.c ft_vsnprintf.c

STRCONV					= ft_atoi.c ft_btoll.c

INTCONV					= ft_itoa.c ft_lltob.c ft_ulltob.c ft_ulllenb.c

UNICODE					= ft_runelen.c ft_buf_utf8.c ft_encode_utf8.c

VECTOR					= ft_vector_new.c ft_vector_append.c					\
						ft_vector_foreach.c ft_vector_destroy.c				\
						ft_vector_insert.c ft_vector_delete.c					\
						ft_vector_linsearch.c ft_vector_binsearch.c			\
						ft_vector_get.c ft_vector_set.c						\
						ft_vector_reverse.c ft_vector_shift.c					\
						ft_vector_rotate.c ft_vector_issorted.c				\
						ft_vector_sinsert.c ft_vector_dup.c					\
						ft_vector_concat.c ft_vector_merge.c					\
						ft_vector_union.c ft_vector_sunion.c					\
						ft_vector_inter.c ft_vector_sinter.c					\
						ft_vector_sub.c ft_vector_ssub.c						\
						ft_vector_uniq.c	ft_vector_suniq.c					\
						ft_vector_length.c ft_vector_size.c					\
						ft_vector_int_resize.c ft_vector_capacity.c			\
						ft_vector_set_length.c ft_vector_sort.c				\
						ft_vector_last.c ft_vector_get_array.c

CLA						= ft_cla_init.c ft_cla_str_var.c ft_cla_int_var.c	\
						ft_cla_bool_var.c ft_cla_pos_var.c					\
						ft_cla_sanity_check.c ft_cla_get_config.c

STRING					= ft_string_new_fill.c ft_string_output.c			\
						  ft_string_new_cstr.c ft_string_destroy.c			\
						  ft_string_tocstring.c ft_string_append_cstr.c		\
						  ft_string_append.c ft_string_at.c					\
						  ft_string_length.c ft_string_size.c				\
						  ft_string_capacity.c ft_string_reserve.c			\
						  ft_string_replacechar.c ft_string_findchar.c		\
						  ft_string_findcsubset.c ft_string_findsubset.c	\
						  ft_string_subset.c ft_string_split.c				\
						  ft_string_new.c ft_string_btoll.c					\
						  ft_string_cstrstr.c ft_string_csubst.c			\
						  ft_string_cmp.c ft_string_destroy_split.c			\
						  ft_string_append_char.c ft_string_set_length.c

STACK					= ft_stack_new.c ft_stack_destroy.c ft_stack_push.c	\
						  ft_stack_pop.c ft_stack_peek.c ft_stack_isempty.c	\
						  ft_stack_size.c

GC						= ft_gc_new.c ft_gc_destroy.c ft_gc_wipe.c			\
						  ft_gc_add.c


SRCS					= $(CORE) $(CSTRING) $(CTYPE) $(IO) $(STRCONV)		\
						$(INTCONV) $(UNICODE) $(CLA) $(VECTOR)				\
						$(STRING) $(STACK) $(GC)

# ~~~~~~~~~~   OBJECTS   ~~~~~~~~~~

OBJ_DIR					= ./.obj
OBJS					= $(SRCS:%.c=$(OBJ_DIR)/%.o)

# ~~~~~~~~~~   RULES    ~~~~~~~~~~


all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "AR\t$(NAME)\n"

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

install:
	./install.sh

# Test the libft

norm:
	@norminette ./src
	@norminette ./include

test: $(NAME)
	@make re -C test
	@printf "\033[0;35mRunning tests\033[0m...\n"
	@./test/test.out

# Compilation rule for each C file.
$(OBJ_DIR)/%.o:%.c
	@$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -g -c $< -o $@
	@printf "CC\t$<\n"

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

.PHONY: all clean fclean re test
