NAME			=	minishell

SRC_DIR			=	src/
OBJ_DIR			=	obj/
LFT_DIR			=	src/libft/
BUILTINS_PATH	=	src/builtin/
EXEC_PATH		=	src/exec/
PARSE_PATH		=	src/parse/
UTILS_PATH		=	src/utils/
BUILDER_PATH	=	src/builder/
SIGNAL_PATH		=	src/signals/
PARSE_PATH		=	src/parse/
ENV_VARI_PATH	=	src/env_variable/
TOKEN_PATH		=	src/token/

LIBFT			=	$(LFT_DIR)libft.a

SRCS_M			=	main.c

SRCS_BT			=	builtin_cd.c builtin_env.c builtin_export.c builtin_pwd.c 

SRCS_EX 		=	exec.c exec_redirect.c exec_pipe.c exec_child_utils.c exec_errors.c exec_utils.c

SRCS_PAR 		=	parse.c

SRCS_UTI 		=	utils.c env_utils.c env_utils2.c

SRCS_BLD 		=	builder.c builder_utils.c file.c args.c

SRCS_SIG 		=	signal.c

SRCS_PARSE		=	parse.c			\
					handle_token.c	\
					parse_utils.c

SRCS_ENV_VARI	=	expand_env_variable.c	\
					expand_env_vari_utils.c

SRCS_TOKEN		=	token_type_utils.c	\
					token_utils.c

OBJS			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

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
			 	 	$(addprefix $(ENV_VARI_PATH), $(SRCS_ENV_VARI_PATH))

HEADERS			=	builder.h builtin.h exec.h parsing.h minishell.h signals.h
HEAD			=	includes/
H_DEPS			=	$(addprefix $(HEAD), $(HEADERS))

OBJS			=	$(SRCS:.c=.o)
CC				=	cc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -I ./include -I/opt/homebrew/include

RLFLAG			=	-L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline
OBJF			=	.cache

all:	$(NAME)

$(NAME): $(LIBFT) $(OBJS) $(H_DEPS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(RLFLAG)
	@echo -e "${FBlue}${NAME}${Blue} compiled\n${RESET}"

$(OBJF):	
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c | $(OBJF)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	@make -C $(LFT_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@make -C $(LFT_DIR) clean
	@echo -e "$(FPurple).o files $(Purple)cleaned\n${RESET}"

fclean:	clean
	@$(RM) $(NAME)
	@make -C $(LFT_DIR) fclean
	@echo -e "$(FRed)${NAME}$(Red) cleaned${RESET}\n"

re:	fclean all

.PHONY			:	all	\
					clean	\
					fclean	\
					re
