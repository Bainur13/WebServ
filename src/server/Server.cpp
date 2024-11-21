#include "../../Includes/server_conf.hpp"
#include "../../Includes/Server.hpp"

Server::Server()
{
}

Server::Server(Server const &src)
{
	*this = src;
}

Server::~Server()
{
}

Server &Server::operator=(Server const &src)
{
	if (this != &src)
	{
		this->_server_fd = src._server_fd;
		this->_listen_fd = src._listen_fd;
		this->_client = src._client;
		this->_address = src._address;
		this->_addrlen = src._addrlen;
		this->_epoll_fd = src._epoll_fd;
	}
	return (*this);
}

void Server::Init(Server_conf sconf)
{
	int					opt;

	_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_fd < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		exit(EXIT_FAILURE);
	}
	opt = 1;
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		close(_server_fd);
	}
	_address.sin_family = AF_INET;
	_address.sin_port = htons(sconf.get_port());
	_address.sin_addr.s_addr = sconf.get_host();
	if (bind(_server_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0)
	{
		std::cerr << strerror(errno) << std::endl;
		close(_server_fd);
		exit(EXIT_FAILURE);
	}
	_addrlen = sizeof(_address);
	_listen_fd = listen(_server_fd, MAX_EVENTS);
	if (_listen_fd < 0)
	{
		close(_server_fd);
		close(_listen_fd);
		std::cerr << strerror(errno) << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Server::set_server_fd(int fd)
{
	this->_server_fd = fd;
}

void Server::set_listen_fd(int fd)
{
	this->_listen_fd = fd;
}

void Server::set_client(int fd)
{
	this->_client = fd;
}

void Server::set_address(struct sockaddr_in addr)
{
	this->_address = addr;
}

void Server::set_addrlen(int len)
{
	this->_addrlen = len;
}

void Server::set_epoll_fd(int fd)
{
	this->_epoll_fd = fd;
}

int Server::get_server_fd()
{
	return (this->_server_fd);
}

int Server::get_listen_fd()
{
	return (this->_listen_fd);
}

int Server::get_client()
{
	return (this->_client);
}

struct sockaddr_in Server::get_address()
{
	return (this->_address);
}

int Server::get_addrlen()
{
	return (this->_addrlen);
}

int Server::get_epoll_fd()
{
	return (this->_epoll_fd);
}
