/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_conf.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:26:00 by bainur            #+#    #+#             */
/*   Updated: 2024/10/28 21:56:38 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/server_conf.hpp"

Server_conf::Server_conf()
{
    _port = 8080;
    _host = INADDR_ANY;
}

Server_conf::Server_conf(const Server_conf &copy)
{
    *this = copy;
}

Server_conf &Server_conf::operator=(const Server_conf &copy)
{
    if (this != &copy)
    {
        this->_port = copy._port;
        this->_host = copy._host;
        this->_server_name = copy._server_name;
        this->_root = copy._root;
        this->_error_page = copy._error_page;
        this->_size_limit = copy._size_limit;
        this->_index = copy._index;
        this->_method = copy._method;
        this->_server = copy._server;
        this->_locations = copy._locations;
		this->_cgis = copy._cgis;
    }
    return *this;
}

Server_conf::~Server_conf()
{
}

void Server_conf::init_server()
{
    _server.Init(*this);
}

void Server_conf::set_server_conf_name(const std::vector <std::string> &line_s)
{
    if (line_s.size() != 3)
        error_exit("Error: invalid server name");
    this->_server_name = line_s[1];
}

void Server_conf::set_root(const std::vector <std::string> &line_s)
{
    if (line_s.size() != 3)
        error_exit("Error: invalid root");
    this->_root = line_s[1];
}

void Server_conf::set_sizelimit(const std::vector <std::string> &line_s)
{
    if (line_s.size() != 3 || !isDigits(line_s[1]))
        error_exit("Error: invalid size limit");
    this->_size_limit = ft_atoi_s(line_s[1]);
}

void Server_conf::set_listen(const std::vector <std::string> &line_s)
{
    std::vector<std::string> listen;
    std::vector<std::string> ip_adress;
    if(line_s.size() != 3)
        error_exit("Error: invalid listen");
    listen = split_line(line_s[1], ":");
    if (listen.size() == 2 && !is_goodport(listen[0]))
        error_exit("Error: invalid listen");
    if (listen.size() == 2)
    {
        _port = ft_atoi_s(listen[0]);
        return ;
    }
    ip_adress = split_line(listen[0], ".");
    if (check_ip(ip_adress) == false || !is_goodport(listen[1]))
        error_exit("Error: invalid listen");
    _host = (ft_atoi_s(ip_adress[0]) << 24) + (ft_atoi_s(ip_adress[1]) << 16) + (ft_atoi_s(ip_adress[2]) << 8) + ft_atoi_s(ip_adress[3]);
    _port = ft_atoi_s(listen[1]);
}

void Server_conf::set_error_page(const std::vector<std::string> &line_s)
{
    if (line_s.size() < 3)
        error_exit("Error: invalid error page");
    for (size_t i = 1; i < line_s.size() - 2; i++)
    {
        if (!isDigits(line_s[i]))
            error_exit("Error: invalid error page");
        _error_page[ft_atoi_s(line_s[i])] = line_s[line_s.size() - 2];
    }
}

void Server_conf::set_index(const std::vector<std::string> &line_s)
{
    if (line_s.size() != 3)
        error_exit("Error: invalid index");
    this->_index = line_s[1];
}

void Server_conf::set_method(const std::vector<std::string> &line_s)
{
    if (line_s.size() < 3)
        error_exit("Error: invalid method");
    for (size_t i = 1; i < line_s.size() - 1; i++)
    {
        if (line_s[i] != "GET" && line_s[i] != "POST" && line_s[i] != "DELETE")
            error_exit("Error: invalid method");
        _method.push_back(line_s[i]);
    }
}

void Server_conf::add_location(Location location)
{
    _locations.push_back(location);
}

std::string Server_conf::get_server_conf_name()
{
    return _server_name;
}

std::string Server_conf::get_root()
{
    return _root;
}

int Server_conf::get_sizelimit()
{
    return _size_limit;
}

int Server_conf::get_port()
{
    return _port;
}

uint Server_conf::get_host()
{
    return _host;
}

std::string Server_conf::get_error_page(short error_code)
{
    if (_error_page.find(error_code) == _error_page.end())
        return "";
    return _error_page[error_code];
}

std::string Server_conf::get_index()
{
    return _index;
}

std::vector<std::string> Server_conf::get_method()
{
    return _method;
}

Server Server_conf::get_server()
{
    return _server;
}

std::vector<Location> Server_conf::get_locations()
{
    return _locations;
}
