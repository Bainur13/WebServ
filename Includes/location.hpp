/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:50 by bainur            #+#    #+#             */
/*   Updated: 2024/10/14 19:19:52 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
#include "utils.hpp"

class Location
{
public:
    Location();
    Location(const Location &copy);
    Location &operator=(const Location &copy);
    ~Location();

    void set_path(const std::vector<std::string> &line_s);
    void set_root(const std::vector<std::string> &line_s);
    void set_index(const std::vector<std::string> &line_s);
    void set_error_page(const std::vector<std::string> &line_s);
    void set_redirect(const std::vector<std::string> &line_s);
    void set_method(const std::vector<std::string> &line_s);
    void set_listing(const std::vector<std::string> &line_s);

    std::string get_path();
    std::string get_root();
    std::string get_index();
    std::string get_error_page(short error_code);
    std::pair<short, std::string> get_redirect();
    std::vector<std::string> get_method();
    bool get_listing();

private:
    std::string _path;
    std::string _root;
    std::string _index;
    std::map<short, std::string> _error_page;
    std::pair<short, std::string> _redirect;
    std::vector<std::string> _method;
    bool _listing;
};
#endif
