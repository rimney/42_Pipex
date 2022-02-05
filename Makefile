# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimney <rimney@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/04 12:32:52 by rimney            #+#    #+#              #
#    Updated: 2022/01/04 12:33:58 by rimney           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRC = ft_split.c assist00.c assist01.c

all: $(NAME)

$(NAME): 
	gcc -Wall -Werror -Wextra -o $(NAME) $(SRC) main.c
clean:
	rm -f $(NAME)
fclean: clean
	rm -f $(NAME)
re: fclean all
