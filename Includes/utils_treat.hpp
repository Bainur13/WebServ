#ifndef UTILS_TREAT_HPP
#define UTILS_TREAT_HPP

#include <string>
#include <iostream>
#include <vector>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include "location.hpp"

Location	search_location(std::string &path, Server_conf &server_c);
bool	check_method_right(std::vector<std::string> methods,
		std::string amethod);
std::string get_content_type(const std::string &path);

#endif
