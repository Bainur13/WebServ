#ifndef CONF_HPP
# define CONF_HPP


# include "server.hpp"
# include <cstdlib>
# include <fstream>
# include <iostream>
# include <map>
# include <sstream>
# include <string>
# include <unistd.h>
# include <vector>

# define EXIT_FAILURE 1

class Server;

class Conf
{
  public:
	Conf();
	Conf(const std::string &filename);
	Conf(const Conf &copy);

	Conf &operator=(const Conf &copy);

	Server parse_server(std::ifstream &file);

	~Conf();

  private:
	std::vector<Server> _servers;
};

#endif
