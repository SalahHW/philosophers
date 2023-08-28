# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 17:23:05 by sbouheni          #+#    #+#              #
#    Updated: 2023/08/28 23:20:04 by sbouheni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=			philo
CC 		=			gcc
CFLAGS	=			-Wall -Wextra -Werror
COMPILE	=			$(CC) $(CFLAGS) -pthread -g3
DFLAGS	=			$(CC) $(CFLAGS) -pthread -g3 -fsanitize=thread

SRCS	=			main.c										\
					parser.c									\
					exit.c										\
					utils.c										\
					routine.c									\
					init.c										\
					time.c										\
					routine_utils.c								\

OBJS	=			$(SRCS:.c=.o)

all:				$(NAME)

$(NAME):			$(OBJS)
					$(COMPILE) $(OBJS) -o $(NAME)

%.o:				%.c
					$(COMPILE) -c $< -o $@

debug	:			fclean $(OBJS)
					$(DFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:				clean
	rm -f $(NAME)

re:					fclean all
