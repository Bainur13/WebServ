/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_conf.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:26:11 by bainur            #+#    #+#             */
/*   Updated: 2024/11/21 02:10:48 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CONF_HPP
# define SERVER_CONF_HPP

# include "Cgi.hpp"
# include "Server.hpp"
# include "location.hpp"
# include "utils.hpp"
# include <cstdlib>
# include <fstream>
# include <iostream>
# include <map>
# include <sstream>
# include <string>
# include <unistd.h>
# include <vector>

class	Location;
class	Server;

class Server_conf
{
  public:
	Server_conf();
	Server_conf(const Server_conf &copy);
	Server_conf &operator=(const Server_conf &copy);
	~Server_conf();

	void set_server_conf_name(const std::vector<std::string> &line_s);
	void set_domain(const std::vector<std::string> domain_name);
	void set_root(const std::vector<std::string> &line_s);
	void set_index(const std::vector<std::string> &line_s);
	void set_sizelimit(const std::vector<std::string> &line_s);
	void set_listen(const std::vector<std::string> &line_s);
	void set_error_page(const std::vector<std::string> &line_s);
	void set_method(const std::vector<std::string> &line_s);
	void set_redirect_default_page(std::vector<std::string> redirect_location);
	void set_redirect_form_page(std::vector<std::string> redirect_location);
	void add_cgi(Cgi *cgi);

	std::vector<Cgi *> &get_cgi();
	std::string get_server_conf_name();
	std::string get_root();
	int get_sizelimit();
	std::string get_redirect_default_page();
	std::string get_redirect_success_page();
	std::string get_redirect_fail_page();
	int get_port();
	uint get_host();
	std::string get_domain();
	std::string get_error_page(short error_code);
	std::string get_index();
	std::vector<std::string> get_method();
	Server get_server();
	const std::vector<Location>& get_locations() const;
	std::vector<Location>& get_locations();

	void add_location(Location location);

	void init_server();

  private:
	int _port;
	uint _host;
	std::string _server_name;
	std::string _domain;
	std::string _root;
	std::string _index;
	std::string _redirect_default_page;
	std::string _redirect_success_page;
	std::string _redirect_fail_page;
	std::map<short, std::string> _error_page;
	std::vector<std::string> _method;
	int _size_limit;
	std::vector<Location> _locations;
	std::vector<Cgi *>_activeCgis;
	Server _server;
};

#endif
