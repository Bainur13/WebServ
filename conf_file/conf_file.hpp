#ifndef CONF_FILE_HPP
# define CONF_FILE_HPP

# include "../Server.hpp"
# include <arpa/inet.h>
# include <cstdlib>
# include <cstring>
# include <errno.h>
# include <fstream>
# include <iostream>
# include <netdb.h>
# include <string>
# include <sys/epoll.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>
# include <vector>

class Config
{
  private:
	std::vector<Server> _servers;

  public:
	Config();
	Config(Config const &src);
	~Config();

	Config &operator=(Config const &src);

	bool parse_config(std::string path);
	bool setup_server(Server &serv, std::ifstream &file);
	bool check_server(Server serv);
	std::vector<Server> get_servers();
};

#endif
