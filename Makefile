# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 11:22:27 by tblaase           #+#    #+#              #
#    Updated: 2021/12/21 15:04:04 by tblaase          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# FLAGS
CC = gcc
CFLAGS = -Wall -Wextra -Werror

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
						$(SRC_PATH)utils_one.c

# OBJECTS
OBJ = $(SRC:.c=.o)

# RULES
all: $(NAME)
	@printf "\n"
	@echo $(G)"       _     _     _       _ _ "$(X)
	@echo $(G)" _____|_|___|_|___| |_ ___| | |"$(X)
	@echo $(G)"|     | |   | |_ -|   | -_| | |"$(X)
	@echo $(G)"|_|_|_|_|_|_|_|___|_|_|___|_|_|"$(X)
	@printf "\n\n"

$(SRC_PATH)%.o :$(SRC_PATH)%.c
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