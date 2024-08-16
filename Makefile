SRC = irc.cpp text_processing.cpp cmds/Ping.cpp
CC = c++ -Wall -Wextra -Werror -std=c++98
NAME = irc

all:		$(NAME)

$(NAME):	$(SRC)
			$(CC) -o $(NAME) $(SRC)

fclean:
	rm $(NAME)

re: fclean all
