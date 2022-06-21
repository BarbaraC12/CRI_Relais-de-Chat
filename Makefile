# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcano <bcano@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 18:43:20 by bcano             #+#    #+#              #
#    Updated: 2022/06/21 22:21:30 by anclarma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################################## #
#               COMMAND              #
# ################################## #
CXX			= c++
MKDIR		= mkdir -p
RM			= rm -rf
UNAME		= $(shell uname)

# ################################## #
#              EXEC NAME             #
# ################################## #
NAME		= ircserv

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= srcs
C_FILES		= main.cpp	\
			  Server.cpp
SRCS		= $(patsubst %, $(C_DIR)/%, $(C_FILES))

# ################################## #
#               OBJECTS              #
# ################################## #
O_DIR		= objs
O_FILES		= $(C_FILES:.cpp=.o)
OBJS		= $(patsubst %, $(O_DIR)/%, $(O_FILES))

# ################################## #
#                FLAGS               #
# ################################## #
CXXFLAGS	= -Wall -Wextra -Werror -MMD -MP
CXXFLAGS	+= -std=c++98
LFLAGS		= 
CINCLUDES	= -I ./includes
CLIBS		= 

# ################################## #
#                RULES               #
# ################################## #

all:		$(NAME)

check:	CXX			=  g++
check:	CXXFLAGS	+=  -Weffc++ -pedantic
check:	CXXFLAGS	+=  -Wconversion
check:	CXXFLAGS	+=  -fsanitize=address
check:	CXXFLAGS	+=  -fsanitize=undefined
check:	CXXFLAGS	+=  -g3
check:	LFLAGS		+=  -fsanitize=address
check:	LFLAGS		+=  -fsanitize=undefined
check:	LFLAGS		+=  -g3
check:	fclean $(NAME)

$(NAME):	$(O_DIR) $(OBJS)
			$(CXX) $(OBJS) $(LFLAGS) $(CLIBS) -o $@

$(O_DIR)/%.o: $(C_DIR)/%.cpp
			$(CXX) $(CXXFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR):
			$(MKDIR) $(O_DIR)

clean:
			$(RM) $(O_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

-include	$(OBJS:.o=.d)

.PHONY: all check clean fclean re
