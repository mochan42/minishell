# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 13:27:58 by fakouyat          #+#    #+#              #
#    Updated: 2022/05/13 13:27:58 by fakouyat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# VARIABLES

NAME				:= libft.a

CC					:= gcc
CFLAGS				:= -Wall -Wextra -Werror

RM					:= rm -rf
INCS				:= -I ./inc/
HEADER				:= ./inc/libft.h

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

SRC_FILES			:=	ft_isalpha.c\
						ft_isdigit.c\
						ft_isalnum.c\
						ft_isascii.c\
						ft_isprint.c\
						ft_strlen.c\
						ft_memset.c\
						ft_bzero.c\
						ft_memcpy.c\
						ft_memmove.c\
						ft_strlcpy.c\
						ft_strlcat.c\
						ft_toupper.c\
						ft_tolower.c\
						ft_strchr.c\
						ft_strrchr.c\
						ft_strncmp.c\
						ft_memchr.c\
						ft_memcmp.c\
						ft_strnstr.c\
						ft_atoi.c\
						ft_calloc.c\
						ft_strdup.c\
						ft_substr.c\
						ft_strjoin.c\
						ft_strtrim.c\
						ft_split.c\
						ft_itoa.c\
						ft_strmapi.c\
						ft_striteri.c\
						ft_putchar_fd.c\
						ft_putstr_fd.c\
						ft_putendl_fd.c\
						ft_putnbr_fd.c\
						ft_lstnew.c\
						ft_lstadd_front.c\
						ft_lstsize.c\
						ft_lstlast.c\
						ft_lstadd_back.c\
						ft_lstdelone.c\
						ft_lstclear.c\
						ft_lstiter.c\
						ft_lstmap.c

OBJ_FILES			:= ${SRC_FILES:.c=.o}

SRC					:= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ					:= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# **************************************************************************** #
# RULES

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJ)
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

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(OBJ_DIR)

re : fclean all
	@echo "$(GREEN) Cleaned all and rebuild $(NAME)!$(END_COLOR)"

.PHONY : all clean fclean re
