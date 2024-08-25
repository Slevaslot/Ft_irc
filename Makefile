# Variables
SRC = irc.cpp text_processing.cpp cmds/Ping.cpp cmds/Pass.cpp cmds/Nick.cpp \
      cmds/User.cpp cmds/Join.cpp cmds/Channel.cpp cmds/List.cpp cmds/Kick.cpp \
      cmds/Topic.cpp cmds/Mode.cpp cmds/Invite.cpp cmds/Tools.cpp
OBJ_DIR = obj
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
CC = c++ -Wall -Wextra -Werror -std=c++98
NAME = ircserv

# Couleurs
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

# Règles
all: $(NAME)

# Compilation et édition de liens
$(NAME): $(OBJ)
	@$(CC) -o $@ $^
	@echo "$(GREEN)Linking completed. Executable $(NAME) created.$(RESET)"

# Compilation des .cpp en .o dans le dossier obj
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)/cmds  # Crée les répertoires si nécessaire
	@$(CC) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)Object files cleaned.$(RESET)"

# Nettoyage complet
fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)Executable $(NAME) removed.$(RESET)"

# Recompilation complète
re: fclean all

.PHONY: all clean fclean re
