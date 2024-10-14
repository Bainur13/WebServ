#ifndef SERVER_HPP
# define SERVER_HPP

# include <cstdlib>
# include <fstream>
# include <iostream>
# include <map>
# include <sstream>
# include <string>
# include <unistd.h>
# include <vector>
# include "utils.hpp"
# include "conf_utils.cpp"


class Server
{
    public :
        Server();
        Server(const Server &copy);
        Server &operator=(const Server &copy);
        ~Server();

        void set_server_name(const std::vector <std::string> &line_s);
        void set_root(const std::vector <std::string> &line_s);
        void set_index(const std::vector <std::string> &line_s);
        void set_sizelimit(const std::vector <std::string> &line_s);
        void set_listen(const std::vector <std::string> &line_s);
        void set_error_page(const std::vector <std::string> &line_s);
        void set_method(const std::vector <std::string> &line_s);

        std::string get_server_name();
        std::string get_root();
        int get_sizelimit();
        int get_port();
        uint get_host();
        std::string get_error_page(short error_code);
        std::string get_index();
        std::vector<std::string> get_method();
        
    private :
        int _port;
        uint _host;
        std::string _server_name;
        std::string _root;
        std::string _index;
        std::map<short, std::string> _error_page;
        std::vector<std::string> _method;
        int _size_limit;
};


#endif
