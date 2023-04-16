# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 15:11:52 by lorbke            #+#    #+#              #
#    Updated: 2023/04/16 16:03:10 by seozkan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name macro
NAME = philo

# command macros
CC = gcc
RM = rm -f
ADD_FLAGS = -pthread #-fsanitize=thread
FLAGS = -Wall -Wextra -Werror

# path macros
INC_PATH = inc
OBJ_PATH = obj
SRC_PATH = src

# src and obj files macros
SRC = main.c parse.c philo_utils.c philo.c time.c waitress.c
OBJ = $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# default rule
default: makedir all

# file targets
${NAME}: ${OBJ}
	${CC} ${FLAGS} ${ADD_FLAGS} ${OBJ} -o ${NAME}
	@echo "make: philo success!"
	@sleep 1
	@make clean
	@clear
	

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	${CC} ${FLAGS} ${ADD_FLAGS} -I $(INC_PATH) -c $< -o $@

# phony targets
all: ${NAME}

makedir:
	@mkdir -p $(OBJ_PATH)

clean:
	${RM} -r $(OBJ_PATH)

fclean: clean
	@${RM} ${NAME}

re: fclean makedir all

.PHONY: all clean fclean re