#include "../../Includes/Response.hpp"

Response::Response()
{
	_isCgiRes = false;
}

Response::Response(Response const &src)
{
	*this = src;
}

Response::~Response()
{
}

bool Response::isCgiRes()
{
	return _isCgiRes;
}

void Response::set_cgiRes(bool boolean)
{
	this->_isCgiRes = boolean;
}
Response &Response::operator=(Response const &src)
{
	if (this != &src)
    {
        _line = src._line;
        _header = src._header;
        _body = src._body;
        _isCgiRes = src._isCgiRes;
        _cookies = src._cookies;
		_unsetcookies = src._unsetcookies;
    }
	return (*this);
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

void Response::add_cookie(std::string cookie)
{
	this->_cookies.push_back(cookie);
}

void Response::add_cookietounset(std::string cookie_to_unset)
{
	this->_unsetcookies.push_back(cookie_to_unset);
}

std::vector<std::string> &Response::get_cookies()
{
	return this->_cookies;
}

std::vector<std::string> &Response::get_unsetcookies()
{
	return this->_unsetcookies;
}

std::string Response::final_response()
{
	std::string response;
	response += _line["Version"] + " " + _line["Status"] + " " + _line["Reason"] + "\r\n";
	for (std::map<std::string, std::string>::iterator it = _header.begin(); it != _header.end(); it++)
		response += it->first + ": " + it->second + "\r\n";
	std::cout << "TAILLE DE COOKIES DANS RES => " << _cookies.size() << std::endl;
	for (std::vector<std::string>::iterator it = _cookies.begin(); it != _cookies.end(); it++)
		response += "Set-Cookie: " + (*it) + "\r\n";
	std::cout << "TAILLE DE UNSETCOOKIES DANS RES => " << _unsetcookies.size() << std::endl;
	for (std::vector<std::string>::iterator it = _unsetcookies.begin(); it != _unsetcookies.end(); it++)
		response += "Set-Cookie: " + (*it) + "=; Expires=Thu, 01 Jan 1970 00:00:00 GMT; " + "Path=/;" + "Domain=localhost" + "\r\n";
	response += "\r\n" + _body;
	return (response);
}

void Response::set_line(std::string key, std::string value)
{
	_line[key] = value;
}

void Response::set_header(std::string key, std::string value)
{
	if (key == "Set-Cookie" && _header[key] != "")
	{
		_header[key] += ";" + value;
	}
	else
		_header[key] = value;
}

void Response::set_body(std::string body)
{
	_body = body;
}

void Response::set_cgi(Cgi *cgi)
{
	_cgi = cgi;
}

std::string Response::get_body()
{
	return (_body);
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

Cgi *Response::get_cgi()
{
	return _cgi;
}
