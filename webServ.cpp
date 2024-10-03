#include "webServ.hpp"
#include "conf_file/conf_file.hpp"

int main()
{
    // class Server serv;

    // serv.receive_signal();
    // return 0;

    Config conf;

    conf.parse_config("conf_file/file.conf");
    Server serv = conf.get_servers()[0];
    std::cout << serv.get_server_name() << std::endl;
}
