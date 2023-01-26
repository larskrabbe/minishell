
VPATH = src

NAME = minishell

CC = cc

LDFLAGS    = -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS   = -I/Users/$(USER)/.brew/opt/readline/include

FLAGS =  -lreadline $(CFLAGS) $(LDFLAGS) $(CPPFLAGS)

CFLAGS = -Wextra -Werror -Wall 
SRC = main.c

# OBJ = $(addprefix obj/,$(notdir $(SRC:.c=.o)))

DIR_OBJ = obj/a

LIBFT=$(LIB_DIR)libft.a

LIB_DIR=libft/

LEXER = src/lexer/lexer.c\
		src/lexer/lexer_memory.c\
		src/lexer/is_white_space.c\
		src/lexer/lexer_utiels.c\

ENV =	src/environment/add_var.c \
		src/environment/create_env.c \
		src/environment/delete_env_var.c \
		src/environment/read_env_var.c \
		src/environment/utils_env.c \

EXP =	src/expander/expender.c \
		src/expander/expender_memory.c\
		src/expander/heredoc.c\
		src/expander/open_files.c\
		src/expander/get_exp_str.c\
		src/expander/expend_tools.c\
		src/expander/expender_bside.c

PATH =	src/pathing/get_cmd_path.c

EXEC =	src/executor/cmd_is_builtin.c\
		src/executor/execution.c\
		src/executor/execution_memory.c\
		src/executor/special_checks.c

SIGNAL =	src/signals/signals.c \
			src/signals/signal_handlers.c

MAIN = src/main/main.c

# -L .tester/LeakSanitizer/ -llsan -lc++ 

all:$(NAME)

$(NAME): $(OBJ)
	$(CC) $(SIGNAL) $(LEXER) $(ENV) $(LIBFT) $(EXP) $(PATH) $(EXEC) $(BUILTINS) $(MAIN) -o $(NAME) $(FLAGS)

$(DIR_OBJ)/%.o : %.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

# lexer_main:$(LEXER) $(ENV) | $(LIBFT) 
# 	cc $(FLAGS) $(LEXER) $(ENV) $(LIBFT)
BUILTINS =	src/builtins/echo.c \
			src/builtins/pwd.c \
			src/builtins/env.c \
			src/builtins/export.c \
			src/builtins/unset.c \
			src/builtins/cd.c \
			src/builtins/cd_utils.c \
			src/builtins/export_utils.c \
			src/builtins/exit.c

#lexer_main:$(LEXER) $(ENV) $(BUILTINS) | $(LIBFT)
	#cc $(FLAGS) $(LEXER) $(ENV) $(BUILTINS) $(LIBFT)
	#@cc -L LeakSanitizer/ -llsan -lc++ $(FLAGS) $(LEXER) $(ENV) $(BUILTINS) $(LIBFT)

$(LIBFT):
	make -C $(LIB_DIR)

fclean:
	@rm -f test.out
	@rm -f $(NAME)
	@rm -rf $(DIR_OBJ)

re: fclean all

#need to install brew before we can install and  use readline
#use bre addprefix to see if already installed
brew:
	rm -rf $$HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $$HOME/.brew && echo 'export PATH=$$HOME/.brew/bin:$$PATH' >> $$HOME/.zshrc && source $$HOME/.zshrc && brew update

#to  install readline with brew
readline:
	brew install readline