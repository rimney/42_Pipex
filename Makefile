SRC = ft_split.c ft_parse_command.c assist00.c
NAME = pipex

all: $(NAME)

$(NAME): 
	gcc -Wall -Werror -Wextra -o $(NAME) $(SRC) main.c
clean:
	rm -f $(NAME)
fclean: clean
	rm -f $(NAME)
re: fclean all
