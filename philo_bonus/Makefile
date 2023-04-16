# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 16:42:20 by seozkan           #+#    #+#              #
#    Updated: 2023/04/16 19:46:18 by seozkan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = @gcc
RM = @rm -f
ADD_FLAGS = -pthread #-fsanitize=thread
FLAGS = -Wall -Wextra -Werror

YELLOW = \033[33;49;1m
CYAN = \033[33;36;1m
END = \033[0;0m

INC_PATH = inc
OBJ_PATH = obj
SRC_PATH = src
LIB_PATH = $(SRC_PATH)/ft_lib

SRC = main_bonus.c utils_bonus.c philo_utils_bonus.c philo_bonus.c monitor_bonus.c
OBJ = $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

default: makedir all

${NAME}: ${OBJ}
	${CC} ${FLAGS} ${ADD_FLAGS} ${OBJ} -o ${NAME}
	@clear
	@sleep 0.25
	@echo "$(CYAN)${NAME} ✔️"
	@echo "$(YELLOW)Mandatory files compiled successfully ✔️$(END)"
	@echo "$(CYAN)by seozkan ✔️$(END)"
	
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	${CC} ${FLAGS} ${ADD_FLAGS} -I $(INC_PATH) -c $< -o $@
	@clear
	@echo "$(YELLOW)$@ build$(CYAN) ✔️"
	@sleep 0.1

all: ${NAME}

makedir:
	@mkdir -p $(OBJ_PATH)

clean:
	${RM} -r $(OBJ_PATH)

fclean: clean
	${RM} ${NAME}

re: fclean makedir all

.PHONY: all clean fclean re