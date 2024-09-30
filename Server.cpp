#include "Server.hpp"

Server::Server()
{
	struct epoll_event	event;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		exit(EXIT_FAILURE);
	}
	opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		close(server_fd);
		std::cerr << strerror(errno) << std::endl;
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_port = htons(8080);
	address.sin_addr.s_addr = INADDR_ANY;
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		close(server_fd);
		std::cerr << strerror(errno) << std::endl;
		;
		exit(EXIT_FAILURE);
	}
	addrlen = sizeof(address);
	listen_fd = listen(server_fd, MAX_EVENTS);
	if (listen_fd < 0)
	{
		close(server_fd);
		close(listen_fd);
		std::cerr << strerror(errno) << std::endl;
		exit(EXIT_FAILURE);
	}
	epoll_fd = epoll_create1(0);
	if (epoll_fd == -1)
	{
		std::cerr << strerror(errno) << std::endl;
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	event.events = EPOLLIN;
	event.data.fd = server_fd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1)
	{
		std::cerr << strerror(errno) << std::endl;
		close(server_fd);
		close(epoll_fd);
		exit(EXIT_FAILURE);
	}
}

Server::Server(Server const &src)
{
	*this = src;
}

Server::~Server()
{
	close(server_fd);
	close(listen_fd);
    close(epoll_fd);
}

Server &Server::operator=(Server const &src)
{
	server_fd = src.server_fd;
	listen_fd = src.listen_fd;
	address = src.address;
	client = src.client;
	addrlen = src.addrlen;
	opt = src.opt;
	return (*this);
}

void Server::handle_client(int client_fd)
{
	Response	res;
	Request		req;

	std::string request;
	request = read_fd_to_end(client_fd);
	std::cout << "Request received:" << std::endl;
	std::cout << request << std::endl;
	req.parse_request(request);
	res = treat_request(req);
	std::cout << "Response sent:" << std::endl;
	std::cout << res.final_response() << std::endl;
	send(client_fd, res.final_response().c_str(), res.final_response().size(),
		0);
	close(client_fd);
}

void Server::receive_signal()
{
	struct epoll_event	events[MAX_EVENTS];

	while (1)
	{
		int num_fds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
		if (num_fds == -1)
		{
			std::cerr << strerror(errno) << std::endl;
			close(server_fd);
			close(epoll_fd);
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < num_fds; ++i)
		{
			if (events[i].data.fd == server_fd)
			{
				client = accept(server_fd,
						(struct sockaddr *)&address,
						(socklen_t *)&addrlen);
				if (client < 0)
				{
					std::cerr << strerror(errno) << std::endl;
					continue ;
				}
                struct epoll_event event;
				event.events = EPOLLIN;
				event.data.fd = client;
				if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client, &event) == -1)
				{
					std::cerr << strerror(errno) << std::endl;
					close(client);
					continue ;
				}
			}
			else
			{
				handle_client(events[i].data.fd);
			}
		}
	}
}

int Server::get_server_fd()
{
	return (server_fd);
}

int Server::get_listen_fd()
{
	return (listen_fd);
}

int Server::get_client()
{
	return (client);
}

struct sockaddr_in Server::get_address()
{
	return (address);
}

int Server::get_addrlen()
{
	return (addrlen);
}

int Server::get_opt()
{
	return (opt);
}

int Server::get_epoll_fd()
{
	return (epoll_fd);
}

void Server::set_server_fd(int fd)
{
	server_fd = fd;
}

void Server::set_listen_fd(int fd)
{
	listen_fd = fd;
}

void Server::set_client(int fd)
{
	client = fd;
}

void Server::set_address(struct sockaddr_in addr)
{
	address = addr;
}

void Server::set_addrlen(int len)
{
	addrlen = len;
}

void Server::set_opt(int optw)
{
	opt = optw;
}

void Server::set_epoll_fd(int fd)
{
	epoll_fd = fd;
}
