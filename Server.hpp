#ifndef SERVER_HPP
# define SERVER_HPP

# include "Request.hpp"
# include "Response.hpp"
# include <arpa/inet.h>
# include <cstdlib>
# include <cstring>
# include <errno.h>
# include <iostream>
# include <netdb.h>
# include <string>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>

class Request;

class Server
{
  public:
	Server();
	Server(Server const &src);
	~Server();

	Server &operator=(Server const &src);

	void receive_signal(Server serv, Request req);

    int get_server_fd();
    int get_listen_fd();
    int get_new_socket();
    struct sockaddr_in get_address();
    int get_addrlen();
    int get_opt();

    void set_server_fd(int fd);
    void set_listen_fd(int fd);
    void set_new_socket(int fd);
    void set_address(struct sockaddr_in addr);
    void set_addrlen(int len);
    void set_opt(int opt);

  private:
	int server_fd;
	int listen_fd;
	struct sockaddr_in address;
	int new_socket;
	int addrlen;
	int opt;
};

std::string read_fd_to_end(int fd);
Response treat_request(Request req);

#endif
