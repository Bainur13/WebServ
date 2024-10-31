#include "../../Includes/Response.hpp"

Response::Response()
{
}

Response::Response(Response const &src)
{
	*this = src;
}

Response::~Response()
{
}

Response &Response::operator=(Response const &src)
{
	_line = src._line;
	_header = src._header;
	_body = src._body;
	return (*this);
}

std::vector<std::string> parseCgiResponse(std::string cgiOuput)
{
	(void) cgiOuput;
	std::vector<std::string> tamere;
	return tamere;
}

std::string Response::error_location(std::string error, short error_code, Location &location, Server_conf &server_c)
{
	std::ostringstream oss;
	std::string error_page;

	std::cout << error_page;
	oss << error_code;

	std::string response;
	_line["Version"] = "HTTP/1.1";
	_line["Status"] = oss.str();
	_line["Reason"] = error;
	_header["Content-Type"] = "text/html";
	if (location.get_path() != "")
	{
		error_page = location.get_error_page(error_code);
		if (error_page != "")
		{
			if (location.get_root() != "")
				error_page = location.get_root() + error_page;
			int fd = open(error_page.c_str(), O_RDONLY);
			if (fd == -1)
			{
				error_location("Error 500 : Internal Server Error", 500, location, server_c);
				_header["Content-Length"] = get_body_size();
				return (response);
			}
			_body += read_fd_to_end(fd);
			close(fd);
			_header["Content-Length"] = get_body_size();
			return (response);
		}
	}
	error_page = server_c.get_error_page(error_code);
	if (error_page != "")
	{
		if (server_c.get_root() != "")
			error_page = server_c.get_root() + error_page;
		int fd = open(error_page.c_str(), O_RDONLY);
		if (fd == -1)
		{
			error_location("Error 500 : Internal Server Error", 500, location, server_c);
			_header["Content-Length"] = get_body_size();
			return (response);
		}
		_body += read_fd_to_end(fd);
		close(fd);
	}
	else
		_body += "<html><body><h1>" + error + "</h1></body></html>";
	_header["Content-Length"] = get_body_size();
	return (response);
}

std::string Response::error_basic(std::string error, short error_code, Server_conf &serv)
{
	std::ostringstream oss;
	std::string error_page;

	oss << error_code;
	error_page = serv.get_error_page(error_code);
	std::string response;
	_line["Version"] = "HTTP/1.1";
	_line["Status"] = oss.str();
	_line["Reason"] = error;
	_header["Content-Type"] = "text/html";
	if (error_page != "")
	{
		if (serv.get_root() != "")
			error_page = serv.get_root() + error_page;
		int fd = open(error_page.c_str(), O_RDONLY);
		if (fd == -1)
		{
			error_basic("00 : Internal Server Error", 500, serv);
			_header["Content-Length"] = get_body_size();
			return (response);
		}
		_body += read_fd_to_end(fd);
		close(fd);
	}
	else
		_body += "<html><body><h1>" + error + "</h1></body></html>";
	_header["Content-Length"] = get_body_size();
	return (response);
}

std::string Response::final_response()
{
	std::string response;
	response += _line["Version"] + " " + _line["Status"] + " " + _line["Reason"] + "\r\n";
	for (std::map<std::string,
				  std::string>::iterator it = _header.begin();
		 it != _header.end(); it++)
		response += it->first + ": " + it->second + "\r\n";
	response += "\r\n" + _body;
	return (response);
}

void Response::set_line(std::string key, std::string value)
{
	_line[key] = value;
}

void Response::set_header(std::string key, std::string value)
{
	_header[key] = value;
}

void Response::set_body(std::string body)
{
	_body = body;
}

std::string Response::get_body_size()
{
	size_t len;

	std::string size;
	std::stringstream out;
	len = _body.size();
	out << len;
	size = out.str();
	return (size);
}
