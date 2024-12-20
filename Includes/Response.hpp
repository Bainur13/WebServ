#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "conf.hpp"
#include "location.hpp"
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <map>
#include <netdb.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class Server_conf;
class Location;

class Response
{
private:
	std::map<std::string, std::string> _line;
	std::map<std::string, std::string> _header;
	std::vector<std::string> _cookies;
	std::vector<std::string> _unsetcookies;
	std::string _body;
	bool _isCgiRes;
	Cgi *_cgi;

public:
	Response();
	Response(Response const &src);
	~Response();

	Response &operator=(Response const &src);
	std::string final_response();
	std::string error_location(std::string error, short error_code, Location &location, Server_conf &server_c);
	std::string error_basic(std::string error, short error_code,  Server_conf &server_c);

	void set_line(std::string key, std::string value);
	void set_header(std::string key, std::string value);
	void set_cgiRes(bool boolean);
	void set_body(std::string body);
	void set_cgi(Cgi *cgi);
	void add_cookie(std::string);
	void add_cookietounset(std::string);

	std::string get_body_size();
	std::vector<std::string> &get_cookies();
	std::vector<std::string> &get_unsetcookies();
	std::string get_body();
	Cgi *get_cgi();

	bool isCgiRes();
};

#endif
