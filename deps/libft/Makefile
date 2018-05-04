# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asyed <asyed@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/25 14:05:53 by satkins           #+#    #+#              #
#    Updated: 2018/04/20 12:59:30 by asyed            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCSDIR_LIBFT = libft/
SRCSDIR_PRINTF = printf/
INCLUDES = -I inc/
CC = gcc
FLAGS += -Wall -Wextra -Werror
CFLAGS += -c -Wall -Wextra -Werror 

################################################################################
# SOURCE FILES                                                          #
################################################################################

SRC_LIBFT = \
		ft_atoi \
		ft_bzero \
		ft_isalnum \
		ft_isalpha \
		ft_isascii \
		ft_isdigit \
		ft_isprint \
		ft_lstadd \
		get_next_line \
		ft_memccpy \
		ft_memchr \
		ft_memcmp \
		ft_memcpy \
		ft_memmove \
		ft_memset \
		ft_strcat \
		ft_strchr \
		ft_strcmp \
		ft_strcpy \
		ft_strdup \
		ft_strlcat \
		ft_strlen \
		ft_strncat \
		ft_strncmp \
		ft_strncpy \
		ft_strnstr \
		ft_strrchr \
		ft_strstr \
		ft_tolower \
		ft_toupper \
		ft_memalloc \
		ft_memdel \
		ft_node \
		ft_strnew \
		ft_strdel \
		ft_strclr \
		ft_striter \
		ft_striteri \
		ft_strmap \
		ft_strmapi \
		ft_strequ \
		ft_strnequ \
		ft_strsub \
		ft_strjoin \
		ft_strtrim \
		ft_strsplit \
		ft_itoa \
		ft_putchar \
		ft_putstr \
		ft_putendl \
		ft_putnbr \
		ft_putchar_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_putnbr_fd  \
		ft_strnjoin \
		get_next_line \
		ft_putnstr \
		ft_putnstr_fd \
		ft_handle_error \
		ft_toupper_str \
		ft_ullitoa_base \
		pqueue \
		queue \
		ft_lstnew \
		ft_splitwhitespace \
		stack \
		ft_double_linked_list \
		metaalloc \
		ft_strerror \
		ft_iswhitespace \

SRC_PRINTF = \
		ft_printf \
		ft_printf_fd \
		argument_handlers \
		printer \
		num_format \
		hex_print \
		int_printer \
		uint_printer \
		oct_printer \
		ptr_printer \
		wstr_print \
		wchar_print \
		char_print

OBJSRC = $(patsubst %, %.o, $(addprefix $(SRCSDIR_LIBFT), $(SRC_LIBFT)))
OBJSRC += $(patsubst %, %.o, $(addprefix $(SRCSDIR_PRINTF), $(SRC_PRINTF)))

################################################################################
# COLOR                                                                        #
################################################################################

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RES = \033[0m

################################################################################
# RULES                                                                        #
################################################################################

all: $(NAME)

$(NAME): $(OBJSRC)
	@ echo "$(CYAN)Building static library...$(RES)"
	@ar rc $@ $(OBJSRC)

%.o: %.c
	@ echo "$(CYAN)Compiling $<...$(RES)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@/bin/rm -f $(OBJSRC)
	@ echo "$(RED)Cleaning folders of object files...$(RES)"

fclean: clean
	@/bin/rm -f $(NAME)
	@ echo "$(RED)Removing library file...$(RES)"

re: fclean all
	@ echo "$(GREEN)Library Remade$(RES)"

