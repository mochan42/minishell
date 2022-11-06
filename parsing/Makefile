# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mochan <mochan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/25 13:29:32 by mochan            #+#    #+#              #
#    Updated: 2022/11/06 16:42:34 by mochan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# VARIABLES

NAME				:= parsing.a

CC					:= gcc
CFLAGS				:= -Wall -Wextra -Werror

RM					:= rm -rf
INCS				:= -I ./inc/
HEADER				:= ./inc/parser.h

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

SRC_FILES			:=	prompt.c init.c free.c \
						parsing.c parsing_utils_2.c parsing_utils_3.c \
						parsing_utils_4.c parsing_utils_5.c \
						env.c env_utils_1.c \
						infile.c infile_utils_1.c \
						outfile.c outfile_utils_1.c\
						cmd_opt_arg.c cmd_opt_arg_utils_1.c \
						cmd_opt_arg_utils_2.c cmd_opt_arg_utils_3.c \
						cmd_opt_arg_utils_4.c \
						dollar_sign.c dollar_sign_2.c \
						quotes.c

OBJ_FILES			:= ${SRC_FILES:.c=.o}

SRC					:= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ					:= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# **************************************************************************** #
# RULES

all : $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)$(NAME) compiled :)$(END_COLOR)"
# -C	:	make option that tells make to change directory before execution.

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS)  -c $< -o $@ $(INCS)
# -c	:	gcc option to compile each .c file into .o file.
# $<	:	represents the first prerequisite of the rule (each .c file 
#			contained in the src folder).
# -o	:	gcc option to define the name of the program (output) file :
#			"push_swap".
# $@	:	represents the filename of the target of the rule, i.e. each output
#			file which will be linked with the header file.

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJ_DIR)

re: fclean all
	@echo "$(GREEN) Cleaned all and rebuild $(NAME)!$(END_COLOR)"

.PHONY: all clean fclean re

