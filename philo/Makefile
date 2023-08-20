# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbouheni <sbouheni@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 17:23:05 by sbouheni          #+#    #+#              #
#    Updated: 2023/08/20 14:22:27 by sbouheni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=			philo
CFLAGS	=			-Wall -Wextra -Werror -pthread -g3
COMPILE	=			gcc $(CFLAGS)

SRCS	=			main.c														\
					parser.c													\
					error.c														\
					utils.c														\
					philo.c														\
					routine.c													\

OBJS	=			$(SRCS:.c=.o)

all:				$(NAME)

$(NAME):			$(OBJS)
					$(COMPILE) $(OBJS) -o $(NAME)


clean:
	rm -f $(OBJS)

fclean:				clean
	rm -f $(NAME)

re:					fclean all
