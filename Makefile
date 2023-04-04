# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mibernar <mibernar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 13:05:26 by mibernar          #+#    #+#              #
#    Updated: 2023/04/04 18:32:54 by mibernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADERS_LIST = philo.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SOURCES_LIST = philo.c utils.c table.c states.c time.c
SOURCES_DIRECTORY = ./sources/
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS_DIRECTORY = objects/
OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

CC = gcc
FLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address -pthread
INCLUDES = -I $(HEADERS_DIRECTORY)

# COLORS

GREEN = \033[0;92m
RED = \033[0;91m
CYAN = \033[0;96m
BLUE = \033[0;94m
YELLOW = \033[0;93m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJECTS_DIRECTORY) $(OBJECTS)
	@echo "\n\nStarting compile"
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "$(CYAN)$(NAME):$(RESET) $(GREEN)object files$(RESET) were created."
	@echo "$(CYAN)$(NAME):$(RESET) $(GREEN)$(NAME)$(RESET) was created"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(CYAN)$(NAME):$(RESET) $(GREEN)$(OBJECTS_DIRECTORY)$(RESET) was created"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS) 
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

clean: ## Cleans all the files from Libft and FdF
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(CYAN)$(NAME): $(RED)$(OBJECTS_DIRECTORY)$(RESET) was deleted"
	@echo "$(CYAN)$(NAME): $(RED)object files$(RESET) deleted"

fclean: clean ## Deep cleans 
	@rm -f $(NAME)
	@echo "$(CYAN)$(NAME): $(RED)$(NAME) $(RESET)was deleted"

re: ## Recompiles the project from scratch
	@make fclean
	@make all

help:  ## show this help
	@echo "usage: make [target]"
	@echo ""
	@egrep "^(.+)\:\ .*##\ (.+)" ${MAKEFILE_LIST} | sed 's/:.*##/#/' | column -t -c 2 -s '#'

.PHONY	: re fclean clean all
