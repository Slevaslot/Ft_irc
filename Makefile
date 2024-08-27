# Variables
SRC = irc.cpp text_processing.cpp cmds/Ping.cpp cmds/Pass.cpp cmds/Nick.cpp \
      cmds/User.cpp cmds/Join.cpp cmds/Channel.cpp cmds/List.cpp cmds/Kick.cpp \
      cmds/Topic.cpp cmds/Mode.cpp cmds/Invite.cpp cmds/Tools.cpp server/server.cpp
OBJ_DIR = obj
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
CC = c++ -Wall -Wextra -Werror -std=c++98
NAME = ircserv

# Couleurs
GRE := \e[1;32m
YEL := \e[1;33m
RESET := \033[0m

# Règles
all: $(NAME)

# Compilation et édition de liens
$(NAME): $(OBJ)
	@$(CC) -o $@ $^
	@echo "$(GRE)Linking completed. Executable $(NAME) created.$(RESET)"

# Compilation des .cpp en .o dans le dossier obj
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)/cmds
	@mkdir -p $(OBJ_DIR)/server # Crée les répertoires si nécessaire
	@$(CC) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YEL)Object files cleaned.$(RESET)"

# Nettoyage complet
fclean: clean
	@rm -f $(NAME)
	@echo "$(YEL)Executable $(NAME) removed.$(RESET)"

# Recompilation complète
re: fclean all

.PHONY: all clean fclean re
