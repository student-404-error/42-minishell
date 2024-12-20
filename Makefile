NAME			=	minishell

SRC_DIR			=	src/
OBJ_DIR			=	obj/
LFT_DIR			=	src/libft/
LIBFT			=	$(LFT_DIR)libft.a

FILES			=	main builtin_cd builtin_pwd builtin_env parse#builtin_export parse

SRCS			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

CC				=	cc
RM				=	rm -rf
CFLAGS = -Wall -Wextra -Werror -I ./include -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lcmocka
RLFLAG			=	-L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline
OBJF			=	.cache
TEST_SRCS		=	src/parse/parse.c src/builtin/*.c
TESTS			=	tests/test_tokenizer.c
TARGET			=	run_tests

vpath %.c $(SRC_DIR) $(SRC_DIR)builtin $(SRC_DIR)parse

all				:	$(NAME)

$(NAME)			:	$(LIBFT) $(OBJS)
					$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(RLFLAG)

rt: $(TEST_SRCS) $(TESTS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(TARGET) $(TEST_SRCS) $(TESTS) $(LIBFT) $(LDFLAGS)

$(OBJF)			:	
					mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c | $(OBJF)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT)		:
					make -C $(LFT_DIR)

clean			:
					$(RM) $(OBJ_DIR)
					make -C $(LFT_DIR) clean

fclean			:	clean
					$(RM) $(NAME)
					make -C $(LFT_DIR) fclean

re				:	fclean all

.PHONY			:	all	\
					clean	\
					fclean	\
					re
