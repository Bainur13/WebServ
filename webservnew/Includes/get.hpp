#ifndef GET_HPP
#define GET_HPP

#include "server_conf.hpp"
#include "Response.hpp"
#include "Request.hpp"

class Response;
class Server_conf;
class Request;

bool	get_request(Request &req, Server_conf &server_c, Response &res);

#endif
