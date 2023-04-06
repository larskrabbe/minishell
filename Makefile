# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 20:58:48 by bogunlan          #+#    #+#              #
#    Updated: 2023/04/06 20:58:50 by bogunlan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLES 
VPATH		= src

NAME 		= minishell

CC 			= gcc

LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include
CFLAGS		= -Wextra -Werror -Wall 


FLAGS		=  -lreadline $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) 

VPATH		= ./ src/ src/builtins src/environment src/executor src/expander src/lexer src/main src/pathing src/signals

SRC =		lexer.c\
			lexer_memory.c\
			is_white_space.c\
			lexer_utiels.c\
			lexer_b.c\
			add_var.c \
			create_env.c \
			delete_env_var.c \
			read_env_var.c \
			utils_env.c \
			expender.c \
			expender_memory.c\
			heredoc.c\
			open_files.c\
			get_exp_str.c\
			expend_tools.c\
			expender_bside.c \
			file_proc.c \
			get_cmd_path.c \
			cmd_is_builtin.c\
			execution.c\
			execution_memory.c\
			special_checks.c\
			pipe_redirection.c \
			signals.c \
			signal_handlers.c \
			echo.c \
			pwd.c \
			env.c \
			export.c \
			unset.c \
			cd.c \
			cd_utils.c \
			export_utils.c \
			exit.c \
			export_utils2.c \
			main.c

OBJS_DIR = obj
OBJ = $(addprefix $(OBJS_DIR)/,$(notdir $(SRC:.c=.o)))

#COLORS
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[1;32m
LGREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[1;34m
LBLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \e[0m
UP = "\033[A"
CUT = "\033[K"


# RULES
all: $(NAME)

LIBFT=$(LIB_DIR)libft.a

LIB_DIR=libft/

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) -lc $(OBJ) $(LIBFT) $(FLAGS)  -o $(NAME)
	@printf "%-54b %b" "$(NAME) $(GREEN) compiled succesfully!" "$(GREEN)[√]$(RESET)\n"
	@echo "\033[0;34m░S░E░A░ ░S░H░E░L░L░\033[0m"
	@echo "by"
	@echo "\033[0;33m𝕝𝕜𝕣𝕒𝕓𝕓𝕖 & 𝕓𝕠𝕘𝕦𝕟𝕝𝕒𝕟\033[0m"


$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "%-61b %b" "$(BLUE)compiling: $(LBLUE)$@" "$(GREEN)[√]$(RESET)\n"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)


$(LIBFT):
	make -C $(LIB_DIR)

clean:
	$(RM) -fr $(OBJS_DIR) $(DEPS_DIR)
	@printf "$(NAME) $(YELLOW) cleaned! $(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: clean all

#need to install brew before we can install and  use readline
#use bre addprefix to see if already installed
brew:
	rm -rf $$HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $$HOME/.brew && echo 'export PATH=$$HOME/.brew/bin:$$PATH' >> $$HOME/.zshrc && source $$HOME/.zshrc && brew update

#to  install readline with brew
readline:
	brew install readline
