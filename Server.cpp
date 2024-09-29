#include "Server.hpp"

Server::Server()
{
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
        std::cerr << strerror(errno) << std::endl;;
        exit(EXIT_FAILURE);
    }
    addrlen = sizeof(address);
    listen_fd = listen(server_fd, 10);
    if (listen_fd < 0)
    {
        close(server_fd);
        close(listen_fd);
        std::cerr << strerror(errno) << std::endl;
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
}

Server &Server::operator=(Server const &src)
{
    server_fd = src.server_fd;
    listen_fd = src.listen_fd;
    address = src.address;
    new_socket = src.new_socket;
    addrlen = src.addrlen;
    opt = src.opt;
    return *this;
}

void Server::receive_signal(Server serv, Request req)
{
    std::string request;

    while (1)
    {
        serv.new_socket = accept(serv.server_fd, (struct sockaddr *)&serv.address, (socklen_t *)&serv.addrlen);
        if (serv.new_socket < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(EXIT_FAILURE);
        }
        request = read_fd_to_end(serv.new_socket);
        std::cout << "Request received:" << std::endl;
        std::cout << request << std::endl;
        req.parse_request(request);
        Response res = treat_request(req);
        std::cout << "Response sent:" << std::endl;
        std::cout << res.final_response() << std::endl;
        send (serv.new_socket, res.final_response().c_str(), res.final_response().size(), 0);
        close(serv.new_socket);
    }
}

int Server::get_server_fd()
{
    return server_fd;
}

int Server::get_listen_fd()
{
    return listen_fd;
}

int Server::get_new_socket()
{
    return new_socket;
}

struct sockaddr_in Server::get_address()
{
    return address;
}

int Server::get_addrlen()
{
    return addrlen;
}

int Server::get_opt()
{
    return opt;
}

void Server::set_server_fd(int fd)
{
    server_fd = fd;
}

void Server::set_listen_fd(int fd)
{
    listen_fd = fd;
}

void Server::set_new_socket(int fd)
{
    new_socket = fd;
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

