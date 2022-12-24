VPATH = src

NAME = minishell

CC = cc

FLAGS = -lreadline $(CFLAGS)

CFLAGS = -Wextra -Werror -Wall

SRC = main.c

OBJ = $(addprefix obj/,$(notdir $(SRC:.c=.o)))

DIR_OBJ = obj

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
		src/environment/libft.c

EXP = src/expander/expender.c

all:$(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(LEXER) $(ENV) $(LIBFT) $(EXP) src/main.c -o $(NAME)

$(DIR_OBJ)/%.o : %.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

lexer_main:$(LEXER) $(ENV) | $(LIBFT) 
	cc $(FLAGS) $(LEXER) $(ENV) $(LIBFT)

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