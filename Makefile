

VPATH = src

NAME = minishell

CC = cc

LDFLAGS    = -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS   = -I/Users/$(USER)/.brew/opt/readline/include
CFLAGS     = -Wextra -Werror -Wall 

FLAGS =  -lreadline $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -L ../tester/LeakSanitizer/ -llsan -lc++ 
# FLAGS =  -lreadline $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -fsanitize=address
# FLAGS =  -lreadline $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) 


SRC = 	src/lexer/lexer.c\
		src/lexer/lexer_memory.c\
		src/lexer/is_white_space.c\
		src/lexer/lexer_utiels.c\
		src/lexer/lexer_b.c\
		src/environment/add_var.c \
		src/environment/create_env.c \
		src/environment/delete_env_var.c \
		src/environment/read_env_var.c \
		src/environment/utils_env.c \
		src/expander/expender.c \
		src/expander/expender_memory.c\
		src/expander/heredoc.c\
		src/expander/open_files.c\
		src/expander/get_exp_str.c\
		src/expander/expend_tools.c\
		src/expander/expender_bside.c \
		src/expander/file_proc.c \
		src/pathing/get_cmd_path.c \
		src/executor/cmd_is_builtin.c\
		src/executor/execution.c\
		src/executor/execution_memory.c\
		src/executor/special_checks.c\
		src/executor/pipe_redirection.c \
		src/signals/signals.c \
		src/signals/signal_handlers.c \
		src/builtins/echo.c \
		src/builtins/pwd.c \
		src/builtins/env.c \
		src/builtins/export.c \
		src/builtins/unset.c \
		src/builtins/cd.c \
		src/builtins/cd_utils.c \
		src/builtins/export_utils.c \
		src/builtins/exit.c \
		src/builtins/export_utils2.c \
		src/main/main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

LIBFT=$(LIB_DIR)libft.a

LIB_DIR=libft/

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(LIBFT) $(OBJ) -o $(NAME)
	@echo "\033[0;34m░S░E░A░ ░S░H░E░L░L░\033[0m"
	@echo "by"
	@echo "\033[0;33m𝕝𝕜𝕣𝕒𝕓𝕓𝕖 & 𝕓𝕠𝕘𝕦𝕟𝕝𝕒𝕟\033[0m"

# objs/%.o: %.c | objs
# 	$(CC) -c $< -o $@

# objs:
# 	mkdir objs

$(LIBFT):
	make -C $(LIB_DIR)

clean:
	@rm src/builtins/*.o src/environment/*.o src/executor/*.o \
	src/expander/*.o src/lexer/*.o src/main/*.o src/pathing/*.o src/signals/*.o

fclean:
	@rm -f test.out
	@rm src/builtins/*.o src/environment/*.o src/executor/*.o \
	src/expander/*.o src/lexer/*.o src/main/*.o src/pathing/*.o src/signals/*.o
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@rm -rf $(DIR_OBJ)

re: fclean all

#need to install brew before we can install and  use readline
#use bre addprefix to see if already installed
brew:
	rm -rf $$HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $$HOME/.brew && echo 'export PATH=$$HOME/.brew/bin:$$PATH' >> $$HOME/.zshrc && source $$HOME/.zshrc && brew update

#to  install readline with brew
readline:
	brew install readline
