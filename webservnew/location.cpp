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


