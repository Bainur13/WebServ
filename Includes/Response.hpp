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
	std::string _body;
	bool _isCgiRes;

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
	std::string get_body_size();
	std::string get_body();
	bool isCgiRes();
	void parseCgiResponse(std::string cgiOutput, Response &res);
};

#endif
