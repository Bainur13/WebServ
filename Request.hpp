#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "Server.hpp"
# include <arpa/inet.h>
# include <cstdlib>
# include <cstring>
# include <errno.h>
# include <iostream>
# include <map>
# include <netdb.h>
# include <string>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>

class Request
{
  private:
	std::map<std::string, std::string> request_line;
	std::map<std::string, std::string> request_header;
	std::string request_body;

	void parse_request_line(std::string line);
	void parse_header(std::string header);

  public:
	Request();
	Request(Request const &src);
	~Request();

	Request &operator=(Request const &src);
	void parse_request(std::string request);
	std::string get_request_line(std::string key);
	std::string get_request_header(std::string key);
	std::string get_request_body();
	void print_request();
};

#endif
