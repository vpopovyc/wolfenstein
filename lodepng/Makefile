# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/15 17:08:37 by vpopovyc          #+#    #+#              #
#    Updated: 2017/09/16 16:46:52 by vpopovyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lodepng.a

SRC = lodepng.c

INC = lodepng.h

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo  "\x1b[32m[35%] lodepng   compiled\x1b[0m"

%.o: %.c
	clang -I $(INC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all