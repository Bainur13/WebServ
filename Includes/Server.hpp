#ifndef SERVER_HPP
# define SERVER_HPP

# include <arpa/inet.h>
# include <cstdlib>
# include <cstring>
# include <errno.h>
# include <iostream>
# include <map>
# include <netdb.h>
# include <string>
# include <sys/epoll.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>
# include "conf.hpp"

# define MAX_EVENTS 100

class Server_conf;

class Server
{
    public:
        Server();
        Server(Server const &src);
        ~Server();

        Server &operator=(Server const &src);

        void Init(Server_conf sconf);

        void set_server_fd(int fd);
        void set_listen_fd(int fd);
        void set_client(int fd);
        void set_address(struct sockaddr_in addr);
        void set_addrlen(int len);
        void set_epoll_fd(int fd);

        int get_server_fd();
        int get_listen_fd();
        int get_client();
        struct sockaddr_in get_address();
        int get_addrlen();
        int get_opt();
        int get_epoll_fd();

    private:
        int _server_fd;
        int _listen_fd;
        int _client;
        struct sockaddr_in _address;
        int _addrlen;
        int _epoll_fd;
};


#endif
