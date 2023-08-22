# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbouheni <sbouheni@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 17:23:05 by sbouheni          #+#    #+#              #
#    Updated: 2023/08/23 00:53:40 by sbouheni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=			philo
CFLAGS	=			-Wall -Wextra -Werror -pthread -g3
COMPILE	=			gcc $(CFLAGS)

SRCS	=			main.c										\
					parser.c									\
					error.c										\
					utils.c										\
					routine.c									\
					init.c										\
					time.c										\
					routine_utils.c								\

OBJS	=			$(SRCS:.c=.o)

all:				$(NAME)

$(NAME):			$(OBJS)
					$(COMPILE) $(OBJS) -o $(NAME)


clean:
	rm -f $(OBJS)

fclean:				clean
	rm -f $(NAME)

re:					fclean all
