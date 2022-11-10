VPATH = src

NAME = minishell

CC = cc

FLAGS = -lreadline $(CFLAGS)

CFLAGS = -Wextra -Werror -Wall

SRC = main.c

OBJ = $(addprefix obj/,$(notdir $(SRC:.c=.o)))

DIR_OBJ = obj



all:$(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) src/main.c -o $(NAME)

$(DIR_OBJ)/%.o : %.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

test:
	@echo test
	cc $(FLAGS) notes/test.c -o test.out
	./test.out

fclean:
	@rm -f test.out
	@rm -f $(NAME)
	@rm -rf $(DIR_OBJ)

re: fclean all

#need to install brew before we can install and  use readline
brew:
	rm -rf $$HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $$HOME/.brew && echo 'export PATH=$$HOME/.brew/bin:$$PATH' >> $$HOME/.zshrc && source $$HOME/.zshrc && brew update

#to  install readline with brew
readline:
	brew install readline