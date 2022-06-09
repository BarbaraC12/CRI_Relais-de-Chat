# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcano <bcano@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 18:43:20 by bcano             #+#    #+#              #
#    Updated: 2022/06/07 18:44:35 by bcano            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################################## #
#               COMMAND              #
# ################################## #
CXX			=	c++
MKDIR		=	mkdir -p
RM			=	rm -rf

# ################################## #
#              EXEC NAME             #
# ################################## #
NAME		=	ircserv

# ################################## #
#               SOURCES              #
# ################################## #
# SRC_DIR		= 	./
SRC			=	main.cpp 

# ################################## #
#               OBJECTS              #
# ################################## #
OBJ_DIR		=	./
OBJ			=	${SRC:.cpp=.o}
OBJ			:=	${addprefix ${OBJ_DIR}, ${OBJ}}
DEP			=	${OBJ:.o=.d}

# ################################## #
#                FLAGS               #
# ################################## #
CXXFLAGS		=	-Wall -Wextra -Werror 
CXXFLAGS		+=	-MMD -MP 
CXXFLAGS		+=	-std=c++98
# CXXFLAGS		+=	-I ./

# ################################## #
#                RULES               #
# ################################## #

${OBJ}%.o: ${SRC}%.cpp
	@${MKDIR} ${@D}
	${CXX} ${CXXFLAGS}

${NAME}: ${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} -o $@

all:	${NAME}

clean:
	${RM} ${OBJ} ${DEP}

fclean: clean
	${RM} ${NAME}

re: fclean all


-include ${DEP}

.PHONY: all clean fclean re
