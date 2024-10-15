/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:50:25 by bainur            #+#    #+#             */
/*   Updated: 2024/10/14 19:19:57 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "location.hpp"

Location::Location()
{
    _path = "";
    _root = "";
    _index = "";
    _redirect.first = 0;
    _redirect.second = "";
    _listing = false;
}

Location::Location(const Location &copy)
{
    *this = copy;
}

Location &Location::operator=(const Location &copy)
{
    if (this != &copy)
    {
        this->_path = copy._path;
        this->_root = copy._root;
        this->_index = copy._index;
        this->_error_page = copy._error_page;
        this->_redirect = copy._redirect;
        this->_method = copy._method;
        this->_listing = copy._listing;
    }
    return *this;
}

Location::~Location()
{
}

void Location::set_path(const std::vector<std::string> &line_s)
{
    if (line_s.size() != 3)
        error_exit("Error: invalid location path");
    this->_path = line_s[1];
}

void Location::set_root(const std::vector<std::string> &line_s)
{
    if (line_s.size() != 3)
        error_exit("Error: invalid location root");
    this->_root = line_s[1];
}

void Location::set_index(const std::vector<std::string> &line_s)
{
    if (line_s.size() != 3)
        error_exit("Error: invalid location index");
    this->_index = line_s[1];
}

void Location::set_error_page(const std::vector<std::string> &line_s)
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

void Location::set_redirect(const std::vector<std::string> &line_s)
{
    if (line_s.size() != 4)
        error_exit("Error: invalid redirect");
    if (!isDigits(line_s[1]))
        error_exit("Error: invalid redirect");
    _redirect.first = ft_atoi_s(line_s[1]);
    _redirect.second = line_s[2];
}

void Location::set_method(const std::vector<std::string> &line_s)
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

void Location::set_listing(const std::vector<std::string> &line_s)
{
    if (line_s.size() != 3)
        error_exit("Error: invalid listing");
    if (line_s[1] == "on")
        _listing = true;
    else if (line_s[1] == "off")
        _listing = false;
    else
        error_exit("Error: invalid listing");
}

std::string Location::get_path()
{
    return this->_path;
}

std::string Location::get_root()
{
    return this->_root;
}

std::string Location::get_index()
{
    return this->_index;
}

std::string Location::get_error_page(short error_code)
{
    if (_error_page.find(error_code) == _error_page.end())
        return "";
    return this->_error_page[error_code];
}

std::pair<short, std::string> Location::get_redirect()
{ 
    return this->_redirect;
}

std::vector<std::string> Location::get_method()
{
    if (_method.size() == 0)
    {
        _method.push_back("GET");
        _method.push_back("POST");
    }
    return this->_method;
}

bool Location::get_listing()
{
    return this->_listing;
}


