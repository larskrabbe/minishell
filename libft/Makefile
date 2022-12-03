# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 12:47:46 by lkrabbe           #+#    #+#              #
#    Updated: 2022/08/27 21:16:01 by lkrabbe          ###   ########.fr        #
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

OBJ = $(F_ALLOCATION:.c=.o) $(F_CHECKER:.c=.o) $(F_PRINT:.c=.o) $(F_LIST:.c=.o) $(F_PARSING:.c=.o) $(F_STRING:.c=.o)

%.o: %.c
	$(CC) -c $< -o $@

all:$(NAME)
	make clean

$(NAME):$(OBJ)
	ar -rs $(NAME) $(OBJ)

clean:
	rm -f *.o

fclean:clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all re clean fclean 