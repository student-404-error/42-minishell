# ANSI COLOR CODE
RED		:=	\033[31m
GREEN		:=	\033[32m
YELLOW		:=	\033[33m
BLUE		:=	\033[34m
MAGENTA		:=	\033[35m
CYAN		:=	\033[36m
RESET		:=	\033[0m

SRCS		=	ft_atoi.c	\
				ft_bzero.c	\
				ft_calloc.c	\
				ft_memchr.c	\
				ft_memcmp.c		\
				ft_memcpy.c		\
				ft_memmove.c	\
				ft_memset.c		\
				ft_putendl_fd.c	\
				ft_putstr_fd.c	\
				ft_putnbr_fd.c	\
				ft_putchar_fd.c		\
				ft_strmapi.c	\
				ft_strcmp.c	\
				ft_strncmp.c	\
				ft_strnstr.c	\
				ft_split.c		\
				ft_strrchr.c	\
				ft_free_split.c	\
				ft_error.c		\
				ft_strchr.c		\
				ft_strstr.c		\
				ft_strdup.c		\
				ft_strtrim.c	\
				ft_isalpha.c	\
				ft_isalnum.c	\
				ft_isdigit.c		\
				ft_isascii.c		\
				ft_isprint.c		\
				ft_printf.c		\
				ft_printf_utils.c	\
				ft_print_unsigned.c	\
				ft_print_hex.c		\
				ft_print_ptr.c 		\
				ft_striteri.c		\
				ft_substr.c			\
				ft_strjoin.c		\
				ft_tolower.c		\
				ft_toupper.c		\
				ft_strlcat.c		\
				ft_strlcpy.c		\
				ft_itoa.c			\
				ft_strlen.c			\
				ft_lstnew.c			\
				ft_lstadd_back.c	\
				ft_lstadd_front.c	\
				ft_lstsize.c		\
				ft_lstlast.c		\
				get_next_line.c

INCLUDES	=	../../include
CC		=	cc

CFLAGS		=	-Wall -Werror -Wextra -fPIC -I$(INCLUDES)

OBJS		=	${SRCS:.c=.o}

NAME		=	libft.a

AR		=	ar

ARFLAGS		=	rsc

RM		=	rm -f

# ------------ RULE ------------ #

%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			@$(AR) $(ARFLAGS) $(NAME) $(OBJS)

clean		:
			@$(RM) $(OBJS)
			
fclean		:	clean
			@$(RM) $(NAME)

re		:	fclean	\
			all

.PHONY		:	all	\
			fclean	\
			clean	\
			re
