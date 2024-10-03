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
	std::ifstream _file;

  public:
	Config();
	Config(std::string path);
	Config(Config const &src);
	~Config();

	Config &operator=(Config const &src);

	bool parse_config();
	bool setup_server(Server &serv, std::ifstream &file);
	bool check_server(Server serv);
	void error_put_config(std::string error);
	std::string parse_ascii_setter(std::string line, std::string to_search);
	int	parse_int_setter(std::string line, std::string to_search);
	void parse_error_page(std::string line, std::string to_search, Server &serv);
	std::vector<Server> get_servers();
	void	is_valid_line(std::string line);
	bool unique_symbol(std::string line, char c);
	std::ifstream &get_file();
};

#endif
