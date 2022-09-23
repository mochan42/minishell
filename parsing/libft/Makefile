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

NAME = libft.a

FUNCTIONS = ft_isalpha.c\
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
	ft_putnbr_fd.c

BONUS_FUNCTIONS = ft_lstnew.c\
				  ft_lstadd_front.c\
				  ft_lstsize.c\
				  ft_lstlast.c\
				  ft_lstadd_back.c\
				  ft_lstdelone.c\
				  ft_lstclear.c\
				  ft_lstiter.c\
				  ft_lstmap.c

BONUS_OBJECTS = ${BONUS_FUNCTIONS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJECT_FILES = ${FUNCTIONS:.c=.o}

all : $(NAME)

$(NAME) :
	$(CC) $(CFLAGS) -c $(FUNCTIONS)
	ar rcs $(NAME) ${OBJECT_FILES}

bonus :
	$(CC) $(CFLAGS) -c $(BONUS_FUNCTIONS)
	ar rcs $(NAME) ${BONUS_OBJECTS}

clean : 
	rm -rf ${OBJECT_FILES} ${BONUS_OBJECTS}

fclean : clean
	rm -rf $(NAME)

re : clean all

.PHONY : all clean fclean re
