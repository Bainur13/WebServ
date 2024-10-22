#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "server_conf.hpp"
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
	std::map<std::string, std::string> _request_line;
	std::map<std::string, std::string> _request_header;
	std::string _request_body;
	std::string _error;

	bool parse_request_line(std::string line);
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
	std::string get_error();
	void print_request();
};

#endif
