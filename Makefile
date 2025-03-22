NAME			=	minishell

SRC_DIR			=	src/
OBJ_DIR			=	obj/
LFT_DIR			=	src/libft/
BUILTINS_PATH		=	src/builtins/
EXEC_PATH		=	src/exec/
PARSE_PATH		=	src/parse/
UTILS_PATH		=	src/utils/
BUILDER_PATH		=	src/builder/
SIGNAL_PATH		=	src/signals/
PARSE_PATH		=	src/parse/
ENV_VARI_PATH		=	src/env_variable/
TOKEN_PATH		=	src/token/

LIBFT			=	$(LFT_DIR)libft.a

SRCS_M			=	main.c

SRCS_BT			=	builtin.c bi_errors.c bi_utils.c bi_check.c

SRCS_EX 		=	exec.c exec_redirect.c exec_pipe.c exec_child_utils.c exec_errors.c exec_utils.c

SRCS_UTI 		=	utils.c env_utils.c env_utils2.c

SRCS_BLD 		=	builder.c builder_utils.c file.c args.c

SRCS_SIG 		=	signal.c

SRCS_PARSE		=	parse.c handle_token.c parse_utils.c heredoc.c

SRCS_ENV_VARI	=	expand_variable.c expand_env_vari_utils.c

SRCS_TOKEN		=	token_type_utils.c token_utils.c

SRCS			=	$(addprefix $(SRC_DIR), $(SRCS_M))			\
					$(addprefix $(BUILTINS_PATH), $(SRCS_BT))	\
					$(addprefix $(EXEC_PATH), $(SRCS_EX))		\
				  	$(addprefix $(TOKEN_PATH), $(SRCS_TOK))		\
				  	$(addprefix $(PARSE_PATH), $(SRCS_PAR))		\
				  	$(addprefix $(UTILS_PATH), $(SRCS_UTI))		\
			  		$(addprefix $(BUILDER_PATH), $(SRCS_BLD))	\
			 	 	$(addprefix $(SIGNAL_PATH), $(SRCS_SIG))	\
			 	 	$(addprefix $(PARSE_PATH), $(SRCS_PARSE))	\
			 	 	$(addprefix $(TOKEN_PATH), $(SRCS_TOKEN))	\
			 	 	$(addprefix $(ENV_VARI_PATH), $(SRCS_ENV_VARI))
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

HEADERS			=	builder.h builtin.h exec.h parsing.h minishell.h signals.h structure.h
HEAD			=	includes/
H_DEPS			=	$(addprefix $(HEAD), $(HEADERS))

CC				=	cc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -I ./includes -I/opt/homebrew/include

RLFLAG			=	-lreadline
OBJF			=	.cache

all:	$(NAME)

pr:
	@echo $(SRCS)
pr2:SRCS_ENV_VARI
	@echo $(OBJS)
$(LIBFT):
	@make -C $(LFT_DIR)

$(NAME): $(LIBFT) $(H_DEPS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(RLFLAG)
	@echo -e "${FBlue}${NAME}${Blue} compiled\n${RESET}"

$(OBJF):	
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	make -C $(LFT_DIR) clean
	echo -e "$(FPurple).o files $(Purple)cleaned\n${RESET}"

fclean:	clean
	@$(RM) $(NAME)
	make -C $(LFT_DIR) fclean
	echo -e "$(FRed)${NAME}$(Red) cleaned${RESET}\n"

re:	fclean all

.PHONY			:	all	\
					clean	\
					fclean	\
					re
