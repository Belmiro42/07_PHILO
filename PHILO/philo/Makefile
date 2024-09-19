# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmatos-d <bmatos-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/13 23:05:42 by bmatos-d          #+#    #+#              #
#    Updated: 2024/08/01 07:23:19 by bmatos-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

REMOVE	= 	rm -rf
CC	  	=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g -fsanitize=address
NAME	=	philo
SOURCES	=	_CREATE_THREADS.c	\
			_INITIALISE.c		\
			_LIBERATION.c		\
			_PARSE.c			\
			_PHILOSOPHER.c		\
			_SPLIT.c			\
			_UTILS.c			\
			MAIN.c

OBJECTS	  = $(SOURCES:.c=.o)

all:		$(NAME)

$(NAME): 	$(OBJECTS)
	@ $(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@ echo "Compiled"

clean:
	@ $(REMOVE) $(OBJECTS)

fclean: clean
	@ $(REMOVE) $(NAME)

re: fclean all

.PHONY : clean re fclean all
