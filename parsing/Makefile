# **************************************************************************** #
# VARIABLES

NAME				= parsing.a

MACHINE				:= $(shell uname -s)

CC					:= gcc
CFLAGS				:= -Wall -Wextra -Werror

RM					:= rm -rf
INCS				:= -I ./inc/
LIB_READLINE_MAC	:= -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
LIB_READLINE_LINUX	:= -lreadline
HEADER				:= ./inc/parser.h

LIBFT_DIR			:= libft
LIBFT_A				:= ./libft/libft.a

SRC_DIR				:= ./src/
OBJ_DIR				:= ./obj/

# **************************************************************************** #
# COLORS

GREEN				:= \033[0;92m
YELLOW				:= \033[0;93m
BLUE				:= \033[0;94m
END_COLOR			:= \033[0;39m

# **************************************************************************** #
# SOURCES

SRC = src/prompt.c\
	src/init.c\
	src/free.c\
	src/parsing.c\
	src/executer.c

OBJ			        = ${SRC:.c=.o}

# **************************************************************************** #
# RULES

# all :	$(OBJ_DIR) $(NAME)
all : $(NAME)

$(NAME):
ifeq ($(MACHINE), Darwin)
	@echo "$(BLUE)make $(LIBFT_DIR)$(END_COLOR)"
	make bonus -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -c $(SRC) -L $(LIBFT_A) -L $(LIB_READLINE_MAC)
	@mv -f ./*.o src/
	ar rcs $(NAME) ${OBJ}
	@echo "$(GREEN)$(NAME) compiled :)$(END_COLOR)"
# -C	:	make option that tells make to change directory before execution.
else
	@echo "$(BLUE)make $(LIBFT_DIR)$(END_COLOR)"
	make bonus -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -c $(SRC) -L $(LIBFT_A) -L $(LIB_READLINE_LINUX)
	@mv -f ./*.o src/
	ar rcs $(NAME) ${OBJ}
	@echo "$(GREEN)$(NAME) compiled :)$(END_COLOR)"
# -C	:	make option that tells make to change directory before execution.
endif

#$(OBJ_DIR)%.o : $(SRC_DIR)%.c
#	$(CC) $(CFLAGS)  -c $< -o $@ $(INCS)
# -c	:	gcc option to compile each .c file into .o file.
# $<	:	represents the first prerequisite of the rule (each .c file 
#			contained in the src folder).
# -o	:	gcc option to define the name of the program (output) file :
#			"push_swap".
# $@	:	represents the filename of the target of the rule, i.e. each output
#			file which will be linked with the so_long.h header file.

#$(OBJ_DIR):
# 	@mkdir $(OBJ_DIR)

clean: 
	$(RM) $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJ)
	make fclean -C $(LIBFT_DIR)

re: fclean all
	@echo "$(GREEN) Cleaned all and rebuild $(NAME)!$(END_COLOR)"

.PHONY:		all clean fclean re

