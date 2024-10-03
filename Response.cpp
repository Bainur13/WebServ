#include "Response.hpp"

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

std::string Response::error_400(std::string error)
{
	std::string response;
	response += "HTTP/1.1 400 Bad Request\r\n";
	response += "Content-Type: text/html\r\n";
	response += "\r\n";
	response += "<html><body><h1>" + error + "</h1></body></html>";
	return (response);
}

std::string Response::final_response()
{
	std::string response;
	response += _line["Version"] + " " + _line["Status"] + " " + _line["Reason"]
		+ "\r\n";
	for (std::map<std::string,
		std::string>::iterator it = _header.begin(); it != _header.end(); it++)
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
	size_t	len;

	std::string size;
	std::stringstream out;
	len = _body.size();
	out << len;
	size = out.str();
	return (size);
}
