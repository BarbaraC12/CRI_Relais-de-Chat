# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 18:53:23 by jdidier           #+#    #+#              #
#    Updated: 2022/07/04 13:26:27 by jdidier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= bot

C_DIR		= srcs
I_DIR		= includes
O_DIR		= objects

SRC			= main.cpp \
			  BotBase.cpp \



OBJ			= ${addprefix ${O_DIR}/,$(SRC:.cpp=.o)}
DEP			= $(OBJ:.o=.d)

CC			= c++
FLAGS		= -Wall -Werror -Wextra -std=c++98 -g3 -fsanitize=address

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) $(OBJ) -o $(NAME)

-include $(DEP)

%.o:%.cpp
	$(CC) -MMD $(FLAGS) -c $< -o $@

$(O_DIR)/%.o:	$(C_DIR)/%.cpp
				[ -d $(O_DIR) ] || mkdir -p $(O_DIR)
				$(CC) $(FLAGS) -I $(I_DIR) -c $< -o $@

clean:
			rm -f $(OBJ) $(DEP)
			rm -rf $(O_DIR)

fclean:		clean
			rm -f $(NAME)
			rm -rf $(O_DIR)

re:			fclean all

.PHONY:		all clean fclean re