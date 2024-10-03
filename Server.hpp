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

	void Init();
	void receive_signal();
	void handle_client(int client_fd);

	int get_server_fd();
	int get_listen_fd();
	int get_client();
	struct sockaddr_in get_address();
	int get_addrlen();
	int get_opt();
	int get_epoll_fd();
	std::string get_server_name();
	std::string get_root();
	std::string get_error_page(short code);
	int get_size_limit();
	int get_port();

	void set_server_fd(int fd);
	void set_listen_fd(int fd);
	void set_client(int fd);
	void set_address(struct sockaddr_in addr);
	void set_addrlen(int len);
	void set_opt(int opt);
	void set_epoll_fd(int fd);
	void set_server_name(std::string name);
	void set_root(std::string root);
	void set_error_page(short code, std::string error_pagew);
	void set_size_limit(int size_limit);
	void set_port(int port);

  private:
	int port;
	std::string server_name;

	std::string root;
	std::map<short, std::string> error_page;
	int size_limit;

	int server_fd;
	int listen_fd;
	struct sockaddr_in address;
	int addrlen;
	int opt;

	int epoll_fd;
	int client;
};

std::string read_fd_to_end(int fd);
Response	treat_request(Request req);

#endif
