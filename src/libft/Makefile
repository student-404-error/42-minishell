# ANSI COLOR CODE
RED		:=	\033[31m
GREEN		:=	\033[32m
YELLOW		:=	\033[33m
BLUE		:=	\033[34m
MAGENTA		:=	\033[35m
CYAN		:=	\033[36m
RESET		:=	\033[0m

FILES		=		ft_atoi			\
				ft_bzero 		\
				ft_calloc  		\
				ft_memchr 		\
				ft_memcmp 		\
				ft_memcpy 		\
				ft_memmove	 	\
				ft_memset 		\
				ft_putendl_fd 		\
				ft_putstr_fd 		\
				ft_putnbr_fd 		\
				ft_putchar_fd 		\
				ft_strmapi 		\
				ft_strcmp 		\
				ft_strncmp 		\
				ft_strnstr	 	\
				ft_split 		\
				ft_strchr 		\
				ft_free_split	 	\
				ft_error 		\
				ft_strrchr 		\
				ft_strstr 		\
				ft_strdup 		\
				ft_strtrim 		\
				ft_isalpha 		\
				ft_isalnum 		\
				ft_isdigit 		\
				ft_isascii 		\
				ft_isprint 		\
				ft_printf 		\
				ft_printf_utils 	\
				ft_print_unsigned 	\
				ft_print_hex 		\
				ft_print_ptr  		\
				ft_striteri 		\
				ft_substr		\
				ft_strjoin 		\
				ft_tolower 		\
				ft_toupper 		\
				ft_strlcat 		\
				ft_strlcpy 		\
				ft_itoa 		\
				ft_strlen 		\
				ft_lstnew		\
				ft_lstadd_back 		\
				ft_lstadd_front 	\
				ft_lstsize 		\
				ft_lstlast 		\
				get_next_line		\
				ft_free_all

INCLUDES	=	../../include
CC		=	cc

CFLAGS		=	-Wall -Werror -Wextra -fPIC -I$(INCLUDES)

SRC_DIR		=	./
OBJ_DIR		=	../../obj/
SRCS		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))
OBJF		=	.cache
NAME		=	libft.a

AR		=	ar

ARFLAGS		=	rsc

RM		=	rm -f

# ------------ RULE ------------ #

$(OBJF):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re
