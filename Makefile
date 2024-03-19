# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/04 18:16:30 by eguelin           #+#    #+#              #
#    Updated: 2024/03/19 15:43:15 by naterrie         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re
.SILENT:

# **************************************************************************** #
#                                   Variable                                   #
# **************************************************************************** #

NAME		= ircserv
OBJS_DIR	= .objs/
SRCS_DIR	= srcs/
INC_DIR		= includes/
CC			= c++
CFLAGS		= -Wall -Werror -Wextra -std=c++98 -g3
INC			= -I $(INC_DIR) -I includes/class/
RM			= rm -fr

# **************************************************************************** #
#                                    Colors                                    #
# **************************************************************************** #

BLACK	= \033[30m
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m
PURPLE	= \033[35m
CYAN	= \033[36m
WHITE	= \033[37m
DEFAULT	= \033[0m

# **************************************************************************** #
#                                    Message                                   #
# **************************************************************************** #

COMP_MSG		= "$(GREEN)Compilation $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)"
CLEAN_MSG		= "$(RED)Cleaning $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)"
FULL_CLEAN_MSG	= "$(PURPLE)Full cleaning $(NAME) $(DEFAULT)done on $(YELLOW)$(shell date +'%Y-%m-%d %H:%M:%S')$(DEFAULT)"

# **************************************************************************** #
#                                    Sources                                   #
# **************************************************************************** #

#  example below

 ALL_FILES		=	main.cpp \

CLASS_DIR		=	class/
CLASS_FILES		=	Server.cpp\
					Client.cpp\
					Channel.cpp\

ALL_FILES		+= $(addprefix $(CLASS_DIR), $(CLASS_FILES))

# SOCKET_DIR	= socket/
# SOCKET_FILES	= Socket.cpp
# ALL_FILES		+= $(addprefix $(SOCKET_DIR), $(SOCKET_FILES))

COMMAND_DIR		=	command/
COMMAND_FILES	=	Invite.cpp\
					Join.cpp\
					Message.cpp\
					Nick.cpp\
					Pass.cpp\
					Privmsg.cpp\
					User.cpp

ALL_FILES		+= $(addprefix $(COMMAND_DIR), $(COMMAND_FILES))

#PARSE_DIR		= parsing/
#PARSE_FILES		= Request.cpp
#ALL_FILES		+= $(addprefix $(PARSE_DIR), $(PARSE_FILES))

OBJ_FILES		= $(addprefix $(OBJS_DIR), $(ALL_FILES:.cpp=.o))

DEP_FILES		= $(OBJ_FILES:.o=.d)

ALL_OBJS_DIR	= $(sort $(dir $(OBJ_FILES)))

# **************************************************************************** #
#                                     Rules                                    #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INC) $(OBJ_FILES) -o $(NAME)
	echo $(COMP_MSG)

$(OBJS_DIR)%.o:  $(SRCS_DIR)%.cpp | $(ALL_OBJS_DIR)
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)
	echo $(CLEAN_MSG)

fclean: clean
	$(RM) $(NAME)
	echo $(FULL_CLEAN_MSG)

re: fclean all

run: all
	./$(NAME) 4343 Password

leaks: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./$(NAME) 4343 Password

$(ALL_OBJS_DIR):
	mkdir -p $@

-include $(DEP_FILES)
