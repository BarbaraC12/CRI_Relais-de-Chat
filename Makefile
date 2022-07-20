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
#              OVER EXEC             #
# ################################## #
NAME2		= bot

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= srcs
C_FILES		= main.cpp	\
			  bnf.cpp	\
			  channel_oper.cpp \
			  Channel.cpp \
			  connect_msg.cpp \
			  miscellaneous_msg.cpp \
			  Param.cpp \
			  server_queries_cmd.cpp \
			  Server.cpp	\
			  user_queries.cpp \
			  User.cpp
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
# CXXFLAGS	+= -Weverything
LFLAGS		= 
CINCLUDES	= -I ./includes
CLIBS		= 

# ################################## #
#                RULES               #
# ################################## #

all:		$(NAME) $(NAME2)

check:	CXX			=  g++
check:	CXXFLAGS	+=  -Weffc++ -pedantic
check:	CXXFLAGS	+=  -Wconversion
check:	CXXFLAGS	+=  -fsanitize=address
check:	CXXFLAGS	+=  -fsanitize=undefined
check:	CXXFLAGS	+=  -g3
check:	LFLAGS		+=  -fsanitize=address
check:	LFLAGS		+=  -fsanitize=undefined
check:	LFLAGS		+=  -g3
check:	fclean $(NAME) $(NAME2)

$(NAME):	$(O_DIR) $(OBJS)
			$(CXX) $(OBJS) $(LFLAGS) $(CLIBS) -o $@
$(NAME2):
			make -C ./bot all CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)" LFLAGS="$(LFLAGS)"

$(O_DIR)/%.o: $(C_DIR)/%.cpp
			$(CXX) $(CXXFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR):
			$(MKDIR) $(O_DIR)

clean:
			$(RM) $(O_DIR)
			make -C ./bot fclean

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

-include	$(OBJS:.o=.d)

.PHONY: all check clean fclean re bot
