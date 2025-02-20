# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 18:18:43 by jaoh              #+#    #+#              #
#    Updated: 2024/08/01 18:18:43 by jaoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL=  /bin/bash

FBlack			=   $(shell echo -e "\033[1;30m")
Black			=   $(shell echo -e "\033[0;30m")
FRed			=   $(shell echo -e "\033[1;31m")
Red				=   $(shell echo -e "\033[0;31m")
FGreen          =   $(shell echo -e "\033[1;32m")
Green           =   $(shell echo -e "\033[0;32m")
FBrown		    =   $(shell echo -e "\033[1;33m")
Brown           =   $(shell echo -e "\033[0;33m")
FYellow         =   $(shell echo -e "\033[1;33m")
Yellow          =   $(shell echo -e "\033[0;33m")
FBlue           =   $(shell echo -e "\033[1;34m")
Blue            =   $(shell echo -e "\033[0;34m")
FPurple         =   $(shell echo -e "\033[1;35m")
Purple          =   $(shell echo -e "\033[0;35m")
FCyan           =   $(shell echo -e "\033[1;36m")
Cyan            =   $(shell echo -e "\033[0;36m")
FWhite          =   $(shell echo -e "\033[1;37m")
White           =   $(shell echo -e "\033[0;37m")
RESET           =   $(shell echo -e "\033[0m")

NAME		= libft.a

SRCS_LIBC	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		  ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		  ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		  ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		  ft_atoi.c ft_calloc.c ft_strdup.c ft_strcmp.c ft_atof.c ft_strndup.c \
		  ft_atol.c

SRCS_ARRAY	= ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
		  ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		  ft_putnbr_fd.c ft_split_quote.c ft_advanced_sort_string_tab.c \
		  ft_arr_size.c ft_free_all.c ft_split2.c ft_ltoa.c

SRCS_LIST	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
		  ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		  ft_lstclear.c ft_lstiter.c ft_lstmap.c

SRCS_PRINTF	= ft_print_char.c ft_print_digit.c ft_printf.c ft_print_mem.c \
		  ft_print_spec.c ft_print_str.c ft_is_spec.c

SRCS_GNL	= get_next_line.c get_next_line_utils.c

HEADERS = ft_printf.h get_next_line.h libft.h

LIBC_PATH	= srcs/libc/
ARRAY_PATH	= srcs/array/
LIST_PATH	= srcs/list/
PRINTF_PATH	= srcs/ft_printf/
GNL_PATH	= srcs/gnl/

SRCS		= $(addprefix $(LIBC_PATH), $(SRCS_LIBC)) \
		  $(addprefix $(ARRAY_PATH), $(SRCS_ARRAY)) \
		  $(addprefix $(LIST_PATH), $(SRCS_LIST)) \
		  $(addprefix $(PRINTF_PATH), $(SRCS_PRINTF)) \
		  $(addprefix $(GNL_PATH), $(SRCS_GNL))

OBJS 			= ${SRCS:.c=.o}

HEAD		= includes/

HDRS_DEPS	= $(addprefix $(HEAD), $(HEADERS))

CFLAGS		= -Wall -Wextra -Werror

ARC		= ar rcs

CC		= cc

all: ${NAME}

${NAME}: ${OBJS}
	ar -rcs ${NAME} ${OBJS}
	@echo -e "${FBlue}${NAME}${Blue} compiled\n${RESET}"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEAD)

clean:
	@rm -f ${OBJS}
	@echo -e "$(FPurple).o files $(Purple)cleaned\n${RESET}"


fclean: clean
	@rm -f ${NAME}
	@echo -e "$(FRed)${NAME}$(Red) cleaned${RESET}\n"
	
re : fclean all

.PHONY: all clean fclean re