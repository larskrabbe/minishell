
FLAGS = -lreadline $(CFLAGS)

CFLAGS = -Wextra -Werror -Wall

all:

test:
	@echo test
	cc $(FLAGS) notes/test.c -o test.out
	./test.out

fclean:
	@rm -f test.out

#need to install brew before we can install and  use readline
brew:
	rm -rf $$HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $$HOME/.brew && echo 'export PATH=$$HOME/.brew/bin:$$PATH' >> $$HOME/.zshrc && source $$HOME/.zshrc && brew update

#to  install readline with brew
readline:
	brew install readline