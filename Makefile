# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asadanow <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 16:58:17 by asadanow          #+#    #+#              #
#    Updated: 2022/12/16 17:30:11 by asadanow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = ./src/pipex.c \
      ./src/pipex_utils.c \
	  ./src/split_pipex.c \
	  ./src/errors_utils.c

LIBDIR = ./libft/

CC = cc -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cd $(LIBDIR) && $(MAKE)
	$(CC) $(OBJ) ./libft/libft.a -o $(NAME)

.c.o:
	$(CC) -c $< -I ./includes -o $@

clean:
	/bin/rm -f $(OBJ)
	cd $(LIBDIR) && $(MAKE) clean

fclean: clean
	/bin/rm -f $(NAME)
	cd $(LIBDIR) && $(MAKE) fclean

re: fclean all
