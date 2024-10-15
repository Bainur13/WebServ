/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:26:11 by bainur            #+#    #+#             */
/*   Updated: 2024/10/14 19:08:30 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CONF_HPP
# define SERVER_CONF_HPP

# include <cstdlib>
# include <fstream>
# include <iostream>
# include <map>
# include <sstream>
# include <string>
# include <unistd.h>
# include <vector>
# include "utils.hpp"
# include "location.hpp"
# include "Server.hpp"

class Location;
class Server;

class Server_conf
{
    public :
        Server_conf();
        Server_conf(const Server_conf &copy);
        Server_conf &operator=(const Server_conf &copy);
        ~Server_conf();

        void set_server_conf_name(const std::vector <std::string> &line_s);
        void set_root(const std::vector <std::string> &line_s);
        void set_index(const std::vector <std::string> &line_s);
        void set_sizelimit(const std::vector <std::string> &line_s);
        void set_listen(const std::vector <std::string> &line_s);
        void set_error_page(const std::vector <std::string> &line_s);
        void set_method(const std::vector <std::string> &line_s);

        std::string get_server_conf_name();
        std::string get_root();
        int get_sizelimit();
        int get_port();
        uint get_host();
        std::string get_error_page(short error_code);
        std::string get_index();
        std::vector<std::string> get_method();
        Server get_server();

        void add_location(Location location);

        void init_server();
        
    private :
        int _port;
        uint _host;
        std::string _server_name;
        std::string _root;
        std::string _index;
        std::map<short, std::string> _error_page;
        std::vector<std::string> _method;
        int _size_limit;

        std::vector<Location> _locations;
        Server _server;
};


#endif
