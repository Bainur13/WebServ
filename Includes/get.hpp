#ifndef GET_HPP
#define GET_HPP

#include "server_conf.hpp"

class Response;
class Request;
class Server_conf;
bool	get_request(Request &req, Server_conf &server_c, Response &res);

#include "Request.hpp"
#include "Response.hpp"
#endif
