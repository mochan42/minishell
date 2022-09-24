# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 14:56:58 by fakouyat          #+#    #+#              #
#    Updated: 2022/06/10 14:56:58 by fakouyat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FUNCTIONS = ft_print_char.c\
			ft_print_hex.c\
			ft_print_int.c\
			ft_print_ptr.c\
			ft_print_str.c\
			ft_print_unsigned.c\
			ft_printf.c
OBJECTS = ${FUNCTIONS:.c=.o}

all : $(NAME)

$(NAME) :
	$(CC) $(CFLAGS) -c $(FUNCTIONS)
	ar rcs $(NAME) $(OBJECTS)

clean : 
	rm -rf $(OBJECTS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
	


		