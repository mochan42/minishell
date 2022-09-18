# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 14:39:49 by fakouyat          #+#    #+#              #
#    Updated: 2022/08/16 14:39:49 by fakouyat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBS = libs/

FT_PRINTF = $(LIBS)ft_printf/

GNL = $(LIBS)gnl/

LIBFT = $(LIBS)libft/

SRCS = srcs/check_input.c\
	srcs/utils.c\
	srcs/parent.c\
	srcs/exec_cmd.c\
	srcs/childs_process.c\
	srcs/utils_2.c\
	srcs/errors.c\
	srcs/utils_3.c\
	srcs/here_doc.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) :
	make -C $(LIBFT)
	make -C $(FT_PRINTF)
	make -C $(GNL)
	$(CC) $(CFLAGS) main.c $(SRCS) $(LIBFT)libft.a $(FT_PRINTF)libftprintf.a $(GNL)gnl.a -o $(NAME)

bonus :
	make -C $(LIBFT)
	make -C $(FT_PRINTF)
	make -C $(GNL)
	$(CC) $(CFLAGS) main_bonus.c $(SRCS) $(LIBFT)libft.a $(FT_PRINTF)libftprintf.a $(GNL)gnl.a -o $(NAME)

clean :
	make clean -C $(LIBFT)
	make clean -C $(FT_PRINTF)
	make clean -C $(GNL)
	rm -rf $(OBJS)

fclean : clean
	make fclean -C $(LIBFT)
	make fclean -C $(FT_PRINTF)
	make fclean -C $(GNL)
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
