/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:50:25 by bainur            #+#    #+#             */
/*   Updated: 2024/12/05 01:15:34 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/location.hpp"
#include "../../Includes/Cgi.hpp"

Location::Location()
{
    _path = "";
    _root = "";
    _index = "";
    _redirect.first = 0;
    _redirect.second = "";
    _listing = false;
	_cgi = NULL;
	_isDatabase = false;
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
        this->_alias = copy._alias;
		this->_cookies = copy._cookies;
		this->_unsetcookies = copy._unsetcookies;
		if (copy.get_cgi())
			this->_cgi = new Cgi(*(copy._cgi));
		else
			this->_cgi = NULL;
		this->_databasePath = copy._databasePath;
		this->_databasePassword = copy._databasePassword;
		this->_isDatabase = copy._isDatabase;
    }
    return *this;
}

Location::~Location()
{
	if (this->get_cgi())
		delete _cgi;
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

void Location::set_cookie(const std::vector<std::string> &line_s)
{
	if (line_s.size() != 3)
		error_exit("Error: invalid cookie syntax");

	if (line_s[1].length() >= 2 && line_s[1][0] == '"' && line_s[1][line_s[1].length() - 1] == '"')
	{
        this->_cookies.push_back(line_s[1].substr(1, line_s[1].length() - 2));
    }
	else
	{
		error_exit("Error: Bad syntax for cookies");
	}
}

void Location::set_database(const std::vector<std::string> &line_s)
{
	if (line_s.size() != 4)
		error_exit("Error: invalid database syntax");

	std::string extension = ".json";

	if (line_s[1].size() > extension.size() && line_s[1].compare(line_s[1].size() - extension.size(), extension.size(), extension) == 0)
	{
		std::ifstream file(line_s[1].c_str());
		if (!file.is_open())
			error_exit("Error: can't open database file");
	}
	else
		error_exit("Error: invalid file name for database");
	_isDatabase = true;
	_databasePath = line_s[1];
	_databasePassword = line_s[2];
}

void Location::set_unsetcookies(const std::vector<std::string> &line_s)
{
	if (line_s.size() != 3)
		error_exit("Error: invalid Unset-cookies syntax");

	if (line_s[1].length() >= 2 && line_s[1][0] == '"' && line_s[1][line_s[1].length() - 1] == '"')
	{
        this->_unsetcookies.push_back(line_s[1].substr(1, line_s[1].length() - 2));
    }
	else
	{
		error_exit("Error: Bad syntax for Unset-cookies");
	}
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
	{
        error_exit("Error: invalid listing");
	}
    if (line_s[1] == "on")
        _listing = true;
    else if (line_s[1] == "off")
        _listing = false;
    else
        error_exit("Error: invalid listing");
}

void Location::set_cgi(const std::vector<std::string> &line_s)
{
	if (line_s.size() != 3)
		error_exit("Error: invalid cgi");
	this->_cgi = new Cgi(line_s[1]);
}

void Location::set_alias(const std::vector<std::string> &line_s)
{
    if (line_s.size() != 3)
        error_exit("Error: invalid alias");
    _alias = line_s[1];
}

std::string Location::getdbpath()
{
	return this->_databasePath;
}
std::string Location::getdbpassword()
{
	return this->_databasePassword;
}
bool Location::isdblocation()
{
	return this->_isDatabase;
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

std::vector<std::string> &Location::get_cookies()
{
	return this->_cookies;
}
std::vector<std::string> &Location::get_unsetcookies()
{
	return this->_unsetcookies;
}

Cgi *Location::get_cgi() const
{
	return (this->_cgi);
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

std::string Location::get_alias()
{
    return this->_alias;
}
