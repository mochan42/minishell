# **************************************************************************** #
# VARIABLES

NAME				:= minishell

MACHINE				:= $(shell uname -s)

CC					:= gcc
CFLAGS				:= -Wall -Wextra -Werror

RM					:= rm -rf

PARSER				:= parsing
EXEC				:= pipex_v

# **************************************************************************** #
# COLORS

GREEN				:= \033[0;92m
YELLOW				:= \033[0;93m
BLUE				:= \033[0;94m
END_COLOR			:= \033[0;39m

# **************************************************************************** #
# RULES

# all :	$(OBJ_DIR) $(NAME)
all : $(NAME)

$(NAME):
ifeq ($(MACHINE), Darwin)
	@echo "$(BLUE)make $(PARSER)$(END_COLOR)"
	make -C $(PARSER)
	@echo "$(BLUE)make $(EXEC)$(END_COLOR)"
	make -C $(EXEC)
	$(CC) $(CFLAGS) $(PARSER)/parsing.a $(EXEC)/pipex.a $(LIB_READLINE_MAC) main -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled :)$(END_COLOR)"
# -C	:	make option that tells make to change directory before execution.
else
	@echo "$(BLUE)make $(PARSER)$(END_COLOR)"
	make -C $(PARSER)
	@echo "$(BLUE)make $(EXEC)$(END_COLOR)"
	make -C $(EXEC)
	$(CC) $(CFLAGS) $(PARSER)/parsing.a $(EXEC)/pipex.a $(LIB_READLINE_LINUX) main.c -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled :)$(END_COLOR)"
# -C	:	make option that tells make to change directory before execution.
endif

clean: 
	$(RM) $(NAME)
	make clean -C $(PARSER)
	make clean -C $(EXEC)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(PARSER)
	make fclean -C $(EXEC)

re: fclean all
	@echo "$(GREEN) Cleaned all and rebuild $(NAME)!$(END_COLOR)"

.PHONY:		all clean fclean re

 : fclean all

.PHONY : all clean fclean re