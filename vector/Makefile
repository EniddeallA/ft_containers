SRC	= main.cpp
NAME= test.out
FLGS= -Wall -Wextra -Werror --std=c++98

all: $(NAME)

$(NAME): $(SRC)
	@c++ $(FLGS) $(SRC) -o $(NAME)

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all