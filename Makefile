# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 13:05:26 by mibernar          #+#    #+#              #
#    Updated: 2022/12/05 12:42:33 by mibernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc -g

FLAGS = -Wall -Wextra -Werror -fsanitize=address -pthread -g -o

HEADERS = philo.h

C_FILES = philo.c utils.c table.c states.c time.c

C_OBJECTS = $(C_FILES:.c=.o)

all:$(NAME)

$(NAME): $(C_OBJECTS)
	@$(CC) $(FLAGS) $(NAME) $(HEADERS) $(C_OBJECTS)

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re