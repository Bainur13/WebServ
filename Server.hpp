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
# include <sys/epoll.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>

# define MAX_EVENTS 100

class		Request;

class Server
{
  public:
	Server();
	Server(Server const &src);
	~Server();

	Server &operator=(Server const &src);

	void receive_signal();
  void handle_client(int client_fd);

	int get_server_fd();
	int get_listen_fd();
	int get_client();
	struct sockaddr_in get_address();
	int get_addrlen();
	int get_opt();
  int get_epoll_fd();

	void set_server_fd(int fd);
	void set_listen_fd(int fd);
	void set_client(int fd);
	void set_address(struct sockaddr_in addr);
	void set_addrlen(int len);
	void set_opt(int opt);
  void set_epoll_fd(int fd);

  private:
	int server_fd;
	int listen_fd;
	int epoll_fd;
	struct sockaddr_in address;
	int client;
	int addrlen;
	int opt;
};

std::string read_fd_to_end(int fd);
Response	treat_request(Request req);

#endif
