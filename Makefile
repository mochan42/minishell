# **************************************************************************** #
# VARIABLES

NAME				:= minishell

MACHINE				:= $(shell uname -s)

CC					:= gcc
CFLAGS				:= -Wall -Wextra -Werror

#LIB_MINISHELL		:= -I .
LIB_READLINE_MAC	:= -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
LIB_READLINE_LINUX	:= -lreadline

RM					:= rm -rf

LIBFT				:= libft
LIBFT_A				:= ./libft/libft.a

GNL					:= gnl
GNL_A				:= ./gnl/gnl.a

PARSER				:= parsing
PARSER_A			:= ./parsing/parsing.a

EXEC				:= pipex_v
EXEC_A				:= ./pipex_v/pipex.a

# **************************************************************************** #
# COLORS

GREEN				:= \033[0;92m
YELLOW				:= \033[0;93m
BLUE				:= \033[0;94m
END_COLOR			:= \033[0;39m

# **************************************************************************** #
# RULES

all : $(NAME)

$(NAME):
ifeq ($(MACHINE), Darwin)
	@echo "$(BLUE)make $(LIBFT) $(END_COLOR)"
	make -C $(LIBFT)
	@echo "$(BLUE)make $(GNL) $(END_COLOR)"
	make -C $(GNL)
	@echo "$(BLUE)make $(PARSER)$(END_COLOR)"
	make -C $(PARSER)
	@echo "$(BLUE)make $(EXEC)$(END_COLOR)"
	make -C $(EXEC)
	@echo "$(BLUE)make $(NAME)$(END_COLOR)"
	$(CC) $(CFLAGS) -I . $(LIBFT_A) $(GNL_A) $(PARSER_A) $(EXEC_A) $(LIB_READLINE_MAC) main.c -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled :)$(END_COLOR)"
# -C	:	make option that tells make to change directory before execution.
else
	@echo "$(BLUE)make $(LIBFT) $(END_COLOR)"
	make -C $(LIBFT)
	@echo "$(BLUE)make $(GNL) $(END_COLOR)"
	make -C $(GNL)
	@echo "$(BLUE)make $(PARSER)$(END_COLOR)"
	make -C $(PARSER)
	@echo "$(BLUE)make $(EXEC)$(END_COLOR)"
	make -C $(EXEC)
	@echo "$(BLUE)make $(NAME)$(END_COLOR)"
	$(CC) $(CFLAGS) main.c -I . $(PARSER_A) $(EXEC_A) $(LIBFT_A) $(GNL_A)  $(LIB_READLINE_LINUX) -o $(NAME)
#	$(CC) $(CFLAGS) -L $(PARSER)/parsing.a -L $(EXEC)/pipex.a $(LIB_READLINE_LINUX) main.c -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled :)$(END_COLOR)"
# -C	:	make option that tells make to change directory before execution.
endif

clean:
	$(RM) $(NAME)
	make clean -C $(LIBFT)
	make clean -C $(GNL)
	make clean -C $(PARSER)
	make clean -C $(EXEC)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJ_DIR)
	make fclean -C $(LIBFT)
	make fclean -C $(GNL)
	make fclean -C $(PARSER)
	make fclean -C $(EXEC)

re: fclean all
	@echo "$(GREEN) Cleaned all and rebuild $(NAME)!$(END_COLOR)"

.PHONY: all clean fclean re
