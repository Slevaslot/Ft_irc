SRC = irc.cpp text_processing.cpp cmds/Ping.cpp cmds/Pass.cpp cmds/Nick.cpp cmds/User.cpp cmds/Join.cpp cmds/Channel.cpp cmds/List.cpp cmds/Kick.cpp cmds/Topic.cpp cmds/Mode.cpp cmds/Invite.cpp
CC = c++ -Wall -Wextra -Werror -std=c++98
NAME = ircserv

all:		$(NAME)

$(NAME):	$(SRC)
			$(CC) -o $(NAME) $(SRC)

fclean:
	rm $(NAME)

re: fclean all
