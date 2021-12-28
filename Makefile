# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 11:22:27 by tblaase           #+#    #+#              #
#    Updated: 2021/12/28 17:57:50 by tblaase          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# FLAGS
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

# COLORS
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

# EXECUTABLE
NAME = ./philo

# PATHS
SRC_PATH = ./src/

# SOURCES
SRC = $(SRC_PATH)main.c \
						$(SRC_PATH)exit.c $(SRC_PATH)init.c $(SRC_PATH)input.c $(SRC_PATH)routine.c $(SRC_PATH)threads.c \
						$(SRC_PATH)utils/utils_one.c

# OBJECTS
OBJ = $(SRC:.c=.o)

# RULES
all: $(NAME)
	@echo $(G)"        __     __ __                           __                     "$(X)
	@echo $(G)".-----.|  |--.|__|  |.-----.-----.-----.-----.|  |--.-----.----.-----."$(X)
	@echo $(G)"|  _  ||     ||  |  ||  _  |__ --|  _  |  _  ||     |  -__|   _|__ --|"$(X)
	@echo $(G)"|   __||__|__||__|__||_____|_____|_____|   __||__|__|_____|__| |_____|"$(X)
	@echo $(G)"|__|                                   |__|                           "$(X)
	@printf "\n\n"

%.o :$(SRC_PATH)%.c
	@echo $(Y)Compiling [$@]...$(X)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf $(UP)$(CUT)
	@echo $(G)Finished [$@]$(X)
	@echo $(UP)$(CUT)

$(NAME): $(OBJ)
	@echo $(Y)Compiling [$(SRC)]...$(X)
	@echo $(G)Finished [$(SRC)]$(X)
	@echo $(Y)Compiling [$(NAME)]...$(X)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo $(G)Finished [$(NAME)]$(X)

clean:
	@if [ -f "$(OBJ)" ]; then \
			rm -f $(OBJ); \
			echo $(R)Cleaning" "[$(OBJ)]...$(X); \
	fi;
# is needed because the above if statement doesn't work
	rm -f $(OBJ)

fclean: clean
	@if [ -f "$(NAME)" ]; then \
			rm -f $(NAME); \
			echo $(R)Cleaning" "[$(NAME)]...$(X); \
	fi;

re: fclean all

# ADDITIONAL RULES

run: all
	$(NAME)

norm:
	@echo $(G)Checking Norminette...$(X)
	@norminette | grep Error | egrep --color '.*Error!|$$' || true
	@echo $(G)Done$(X)

.PHONY: all, clean, fclean, re, run, norm