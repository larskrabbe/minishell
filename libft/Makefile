# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bogunlan <bogunlan@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 12:47:46 by lkrabbe           #+#    #+#              #
#    Updated: 2023/04/06 20:58:12 by bogunlan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

VPATH = allocation checker list parsing print string

HEADER = libft.h

CC = cc

CFLAGS = -Wall -Werror -Wextra

F_ALLOCATION = 	ft_bzero.c\
				ft_calloc.c

F_CHECKER =		ft_isalnum.c\
				ft_isalpha.c\
				ft_isascii.c\
				ft_isdigit.c\
				ft_isprint.c\
				ft_memchr.c\
				ft_memcmp.c\
				ft_strchr.c\
				ft_strncmp.c\
				ft_strnstr.c\
				ft_strrchr.c

F_PRINT = 		calc_length.c\
				create_output.c\
				fill_struct.c\
				ft_printf.c\
				ft_putchar_fd.c\
				ft_putendl_fd.c\
				ft_putnbr_fd.c\
				ft_putstr_fd.c\
				printf_convert.c\
				typesettera.c\
				typesetterb.c

F_LIST =		ft_lstadd_back.c\
				ft_lstadd_front.c\
				ft_lstclear.c\
				ft_lstdelone.c\
				ft_lstiter.c\
				ft_lstlast.c\
				ft_lstmap.c\
				ft_lstnew.c\
				ft_lstsize.c

F_PARSING =		ft_atoi.c\
				ft_itoa.c\
				ft_strlen.c\
				get_next_line.c

F_STRING = 		ft_memcpy.c\
				ft_memmove.c\
				ft_memset.c\
				ft_split.c\
				ft_strdup.c\
				ft_striteri.c\
				ft_strjoin.c\
				ft_strlcat.c\
				ft_strlcpy.c\
				ft_strmapi.c\
				ft_strtrim.c\
				ft_substr.c\
				ft_tolower.c\
				ft_toupper.c

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

OBJ = $(F_ALLOCATION:.c=.o) $(F_CHECKER:.c=.o) $(F_PRINT:.c=.o) $(F_LIST:.c=.o) $(F_PARSING:.c=.o) $(F_STRING:.c=.o)

%.o: %.c
	@$(CC) -c $< -o $@
	@printf "%-61b %b" "$(BLUE)compiling: $(LBLUE)$@" "$(GREEN)[√]$(RESET)\n"

all:$(NAME)
	make clean

$(NAME):$(OBJ)
	@ar -rs $(NAME) $(OBJ)
	@printf "%-54b %b" "$(NAME) $(GREEN) compiled succesfully!" "$(GREEN)[√]$(RESET)\n"

clean:
	rm -f *.o

fclean:clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all re clean fclean 