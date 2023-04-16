# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 16:40:42 by seozkan           #+#    #+#              #
#    Updated: 2023/04/16 16:40:57 by seozkan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
RM = rm -f
ADD_FLAGS = -pthread #-fsanitize=thread
FLAGS = -Wall -Wextra -Werror

INC_PATH = inc
OBJ_PATH = obj
SRC_PATH = src

SRC = main.c utils.c philo_utils.c philo.c waitress.c
OBJ = $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

default: makedir all

${NAME}: ${OBJ}
	${CC} ${FLAGS} ${ADD_FLAGS} ${OBJ} -o ${NAME}
	@echo "make: philo success!"
	@sleep 1
	@make clean
	@clear
	

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	${CC} ${FLAGS} ${ADD_FLAGS} -I $(INC_PATH) -c $< -o $@

all: ${NAME}

makedir:
	@mkdir -p $(OBJ_PATH)

clean:
	${RM} -r $(OBJ_PATH)

fclean: clean
	@${RM} ${NAME}

re: fclean makedir all

.PHONY: all clean fclean re