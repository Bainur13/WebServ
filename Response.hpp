#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "webServ.hpp"
# include <arpa/inet.h>
# include <cstdlib>
# include <cstring>
# include <errno.h>
# include <iostream>
# include <map>
# include <netdb.h>
# include <sstream>
# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>

class Server;

class Response
{
  private:
	std::map<std::string, std::string> _line;
	std::map<std::string, std::string> _header;
	std::string _body;

  public:
	Response();
	Response(Response const &src);
	~Response();

	Response &operator=(Response const &src);
	std::string final_response();
	std::string error_basic(std::string error, short error_code, Server serv);
	void set_line(std::string key, std::string value);
	void set_header(std::string key, std::string value);
	void set_body(std::string body);
	std::string get_body_size();
};

#endif
