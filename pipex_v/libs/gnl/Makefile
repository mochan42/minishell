# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 14:47:53 by fakouyat          #+#    #+#              #
#    Updated: 2022/08/16 14:47:53 by fakouyat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a

SRCS = get_next_line.c get_next_line_utils.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

CC = gcc

all : $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -c $(SRCS)
	ar rcs $(NAME) $(OBJS)

clean : 
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
