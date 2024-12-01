#include "../../Includes/Request.hpp"
#include "assert.h"
#include <cassert>

Request::Request()
{
    _request_line["Method"] = "";
    _request_line["Path"] = "";
    _request_line["Version"] = "";
    _request_body = "";

    _error = "";
}

Request::Request(Request const &src)
{
	*this = src;
}

Request::~Request()
{
}

Request &Request::operator=(Request const &src)
{
	if (this != &src)
	{
		this->_request_line = src._request_line;
		this->_request_header = src._request_header;
		this->_request_body = src._request_body;
	}
	return (*this);
}

bool Request::parse_request_line(std::string line)
{
    if (line == "")
    {
        _error = "Error 400 : No Request Line";
        return false;
    }
    if (line.find(" ") == std::string::npos)
    {
        _error = "Error 400 : Incomplete Request Line";
        return false;
    }
	_request_line["Method"] = line.substr(0, line.find(" "));
    if (line.find(" ") == std::string::npos)
    {
        _error = "Error 400 : Incomplete Request Line";
        return false;
    }
	line = line.substr(line.find(" ") + 1);
	_request_line["Path"] = line.substr(0, line.find(" "));
    if (line.find(" ") == std::string::npos)
    {
        _error = "Error 400 : Incomplete Request Line";
        return false;
    }
	line = line.substr(line.find(" ") + 1);
	_request_line["Version"] = line;
    if (_request_line["Method"] != "GET" && _request_line["Method"] != "POST" && _request_line["Method"] != "DELETE")
    {
        _error =  "Error 400 : Method is incorrect";
        return false;
    }
    if (_request_line["Path"] == "")
    {
        _error = "Error 400 : No Path";
        return false;
    }
    if (_request_line["Version"] != "HTTP/1.1")
    {
        _error = "Error 400 : Version is incorrect";
        return false;
    }
    return true;
}

void Request::parse_header(std::string header)
{
    _request_header[header.substr(0, header.find(":"))] = header.substr(header.find(":") + 2);
}

void Request::parse_request(std::string request)
{
	size_t	pos;

	std::string line;
	std::string header;
	std::string body;

	pos = request.find("\r\n");
	line = request.substr(0, pos);
    if (parse_request_line(line) == 0)
        return;
    request = request.substr(pos + 2);
    while ((pos = request.find("\r\n")) != std::string::npos)
    {
        header = request.substr(0, pos);
        request = request.substr(pos + 2);
        if (header == "")
            break;
        _request_header[header.substr(0, header.find(":"))] = header.substr(header.find(":") + 2);
    }
    _request_body = request;
    if (_request_body != "")
           std::cout << "Body: " << _request_body << std::endl;
    if (_request_line["Method"] == "GET" && _request_body != "")
        _error = "Error 400 : GET request with body";
    if (_request_line["Method"] == "POST" && _request_header.find("Content-Length") == _request_header.end())
        _error = "Error 400 : POST request without Content-Length";
    if (_request_line["Method"] == "POST" && (int)_request_body.size() != atoi(_request_header["Content-Length"].c_str()))
        _error = "Error 400 : POST request with wrong Content-Length";
    if (_request_line["Method"] == "POST" && _request_body == "")
        _error = "Error 400 : POST request without body";
}

std::string Request::get_url_params(std::string path)
{
	return path.substr(path.find_first_of('?') + 1, std::string::npos - 1);
}

std::string Request::get_request_line(std::string key)
{
    return _request_line[key];
}

std::string Request::get_request_header(std::string key)
{
    return _request_header[key];
}

std::string Request::get_request_body()
{
    return _request_body;
}

void Request::print_request()
{
    std::map<std::string, std::string>::iterator it;

    for (it = _request_line.begin(); it != _request_line.end(); it++)
        std::cout << it->first << ": " << it->second << std::endl;
    for (it = _request_header.begin(); it != _request_header.end(); it++)
        std::cout << it->first << ": " << it->second << std::endl;
    std::cout << _request_body << std::endl;
}

std::string Request::get_error()
{
    return _error;
}
