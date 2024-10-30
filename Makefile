SRC =				./src/main.cpp \
					./src/conf/conf.cpp \
					./src/conf/server_conf.cpp \
					./src/server/Server.cpp \
					./src/utils/utils.cpp \
					./src/utils/utils_treat.cpp \
					./src/cgi/cgi.cpp \
					./src/conf/location.cpp \
					./src/format/Response.cpp \
					./src/format/Request.cpp \
					./src/method/get.cpp \
					./src/method/post.cpp \
					./src/method/delete.cpp \
					./src/auto_index/auto_index.cpp \

C++FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -g3

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
	cd ./website && npm run build
	# sleep 3
	# firefox http://localhost:8080

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf ./build

.cpp.o:
	c++ $(C++FLAGS) -c $< -o ${<:.cpp=.o}

re: fclean
	make all

.PHONY: all clean fclean re
