# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 11:22:27 by tblaase           #+#    #+#              #
#    Updated: 2022/01/17 19:23:29 by tblaase          ###   ########.fr        #
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
OBJ_PATH = ./obj/
UTILS_PATH = $(SRC_PATH)utils/

# SOURCES
SRC = $(SRC_PATH)main.c \
						$(SRC_PATH)exit.c $(SRC_PATH)init.c $(SRC_PATH)input.c $(SRC_PATH)reaper.c $(SRC_PATH)routine.c $(SRC_PATH)threads.c\
						$(UTILS_PATH)utils_one.c $(UTILS_PATH)utils_two.c

# OBJECTS
OBJ = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))

# RULES
all: $(NAME)
	@echo $(G)"        __     __ __                           __                     "$(X)
	@echo $(G)".-----.|  |--.|__|  |.-----.-----.-----.-----.|  |--.-----.----.-----."$(X)
	@echo $(G)"|  _  ||     ||  |  ||  _  |__ --|  _  |  _  ||     |  -__|   _|__ --|"$(X)
	@echo $(G)"|   __||__|__||__|__||_____|_____|_____|   __||__|__|_____|__| |_____|"$(X)
	@echo $(G)"|__|                                   |__|                           "$(X)
	@printf "\n\n"

$(OBJ_PATH)%.o :$(SRC_PATH)%.c
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
#	@printf $(UP)$(CUT)
	@echo $(G)Finished [$@]$(X)
#	@echo $(UP)$(CUT)
#	@echo $(Y)Compiling [$(SRC)]...$(X)
#	@echo $(G)Finished [$(SRC)]$(X)

$(NAME): $(OBJ)
	@echo $(Y)Compiling [$(SRC)]
	@echo into [$(NAME)]...$(X)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo $(G)Finished [$(NAME)]$(X)

clean:
	@if [ -d "$(OBJ_PATH)" ]; then \
			rm -f -r $(OBJ_PATH); \
			echo $(R)Cleaning" "[$(OBJ)]...$(X); else \
			echo "No objects(.o-files) to remove."; \
	fi;
# is needed because the above if statement doesn't work
#	@rm -f $(OBJ)
#	@echo $(R)Cleaning" "[$(OBJ)]...$(X);

fclean: clean
	@if [ -f "$(NAME)" ]; then \
			rm -f $(NAME); \
			echo $(R)Cleaning" "[$(NAME)]...$(X);else \
			echo "No executable(./philo) to remove."; \
	fi;

re: fclean all

# ADDITIONAL RULES

norm:
	@echo $(G)Checking Norminette...$(X)
	@norminette | grep Error | egrep --color '.*Error!|$$' || true
	@echo $(G)Done$(X)

.PHONY: all, clean, fclean, re, norm
