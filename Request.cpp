#include "Request.hpp"

Request::Request()
{
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
		this->request_line = src.request_line;
		this->request_header = src.request_header;
		this->request_body = src.request_body;
	}
	return (*this);
}

void Request::parse_request_line(std::string line)
{
    if (line == "")
        return;
    if (line.find(" ") == std::string::npos)
    {
        request_line["Method"] = "ERROR";
        return;
    }
	request_line["Method"] = line.substr(0, line.find(" "));
    if (line.find(" ") == std::string::npos)
    {
        request_line["Path"] = "ERROR";
        return;
    }
	line = line.substr(line.find(" ") + 1);
	request_line["Path"] = line.substr(0, line.find(" "));
    if (line.find(" ") == std::string::npos)
    {
        request_line["Version"] = "ERROR";
        return;
    }
	line = line.substr(line.find(" ") + 1);
	request_line["Version"] = line;
}

void Request::parse_header(std::string header)
{
    request_header[header.substr(0, header.find(":"))] = header.substr(header.find(":") + 2);
}

void Request::parse_request(std::string request)
{
	size_t	pos;

	std::string line;
	std::string header;
	std::string body;

	pos = request.find("\r\n");
	line = request.substr(0, pos);
    parse_request_line(line);
    request = request.substr(pos + 2);
    while ((pos = request.find("\r\n")) != std::string::npos)
    {
        header = request.substr(0, pos);
        request = request.substr(pos + 2);
        if (header == "")
            break;
        request_header[header.substr(0, header.find(":"))] = header.substr(header.find(":") + 2);
    }
    request_body = request;
}

std::string Request::get_request_line(std::string key)
{
    return request_line[key];
}

std::string Request::get_request_header(std::string key)
{
    return request_header[key];
}

std::string Request::get_request_body()
{
    return request_body;
}

void Request::print_request()
{
    std::map<std::string, std::string>::iterator it;

    for (it = request_line.begin(); it != request_line.end(); it++)
        std::cout << it->first << ": " << it->second << std::endl;
    for (it = request_header.begin(); it != request_header.end(); it++)
        std::cout << it->first << ": " << it->second << std::endl;
    std::cout << request_body << std::endl;
}
