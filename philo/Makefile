# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 17:23:05 by sbouheni          #+#    #+#              #
#    Updated: 2023/08/27 16:51:49 by sbouheni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=			philo
CFLAGS	=			-Wall -Wextra -Werror -pthread
COMPILE	=			gcc $(CFLAGS)
DFLAGS	=			gcc $(CFLAGS) -g3 -fsanitize=thread

SRCS	=			main.c										\
					parser.c									\
					error.c										\
					utils.c										\
					routine.c									\
					init.c										\
					time.c										\
					routine_utils.c								\
					read_mutex.c								\

OBJS	=			$(SRCS:.c=.o)

all:				$(NAME)

$(NAME):			$(OBJS)
					$(COMPILE) $(OBJS) -o $(NAME)

debug	:			$(OBJS)
					$(DFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:				clean
	rm -f $(NAME)

re:					fclean all
