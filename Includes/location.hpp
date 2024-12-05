/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:50 by bainur            #+#    #+#             */
/*   Updated: 2024/12/04 22:13:59 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "Cgi.hpp"
# include "utils.hpp"
# include <cstdlib>
# include <fstream>
# include <iostream>
# include <map>
# include <sstream>
# include <string>
# include <unistd.h>
# include <vector>

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
	void set_alias(const std::vector<std::string> &line_s);
	void set_cgi(const std::vector<std::string> &line_s);
	void set_cookie(const std::vector<std::string> &line_s);
	void set_unsetcookies(const std::vector<std::string> &line_s);
	void set_database(const std::vector<std::string> &line_s);

	Cgi *get_cgi() const;
	std::string get_path();
	std::string get_root();
	std::string get_index();
	std::string get_alias();
	std::vector<std::string> &get_cookies();
	std::vector<std::string> &get_unsetcookies();
	std::string get_error_page(short error_code);
	std::pair<short, std::string> get_redirect();
	std::vector<std::string> get_method();
	std::string getdbpath();
	std::string getdbpassword();
	bool isdblocation();
	bool get_listing();

  private:
	std::string _databasePath;
	std::string _databasePassword;
	std::string _path;
	std::string _root;
	std::string _index;
	std::string _alias;
	std::vector<std::string> _cookies;
	std::vector<std::string> _unsetcookies;
	std::map<short, std::string> _error_page;
	std::pair<short, std::string> _redirect;
	std::vector<std::string> _method;
	bool _isDatabase;
	bool _listing;
	Cgi *_cgi;
};
#endif
