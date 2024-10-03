#include "webServ.hpp"
#include "conf_file/conf_file.hpp"

int main()
{
    // class Server serv;

    // serv.receive_signal();
    // return 0;

    Config conf("conf_file/file.conf");

    conf.parse_config();
    Server serv = conf.get_servers()[0];
    std::cout << serv.get_server_name() << std::endl;
    std::cout << serv.get_port() << std::endl;
    std::cout << serv.get_root() << std::endl;
    std::cout << serv.get_error_page(404) << std::endl;
    // serv.Init();
    // serv.receive_signal();

}
