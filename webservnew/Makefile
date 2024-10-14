SRC =				main.cpp \
					conf.cpp \
					server.cpp \
					conf_utils.cpp \
					utils.cpp \

C++FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

NAME = WebServ

OBJ = $(SRC:.cpp=.o)

GREEN = \033[0;32m
NC = \033[0m
YELLOW = \e[0;93m
RED = \033[0;31m


$(NAME): $(OBJ)
	c++ $(C++FLAGS) $(OBJ) -o $(NAME)
	@echo "	 			$(RED)+------------------------+\n \
					|  $(YELLOW)     WebServ $(GREEN)[OK]$(RED)     |\n \
					+------------------------+$(NC)"

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

.cpp.o:
	c++ $(C++FLAGS) -c $< -o ${<:.cpp=.o}

re: fclean
	make all

.PHONY: all clean fclean re
