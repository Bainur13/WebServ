#ifndef POST_HPP
#define POST_HPP

#include "server_conf.hpp"
#include "Response.hpp"
#include "Request.hpp"


bool	post_request(Request &req, Server_conf &server_c, Response &res);

#endif
