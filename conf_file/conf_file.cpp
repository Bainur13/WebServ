#include "conf_file.hpp"

Config::Config()
{
}

Config::Config(Config const &src)
{
	*this = src;
}

Config::~Config()
{
}

Config &Config::operator=(Config const &src)
{
	_servers = src._servers;
	return (*this);
}

std::vector<Server> Config::get_servers()
{
	return (_servers);
}


void	serv_name_setter(Server &serv, std::string line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	if ((int)line.find("server_name") != i)
	{
		std::cerr << "serv_name error" << std::endl;
		exit(EXIT_FAILURE);
	}
	i = line.find("server_name") + 12;
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	if (line[i] == ';')
	{
		std::cerr << "empty server name" << std::endl;
		exit(EXIT_FAILURE);
	}
	j = i;
	while (isalnum(line[i]) || line[i] == '.' || line[i] == '-'
		|| line[i] == '_')
		++i;
    if (line[i] != ';')
    {
        std::cerr << "server name error" << std::endl;
        exit(EXIT_FAILURE);
    }
    serv.set_server_name(line.substr(j, i - j));
}

bool Config::setup_server(Server &serv, std::ifstream &file)
{
	std::string line;
    int in_brackets = 0;

    while (std::getline(file, line))
    {
        if (line == "{")
        {
            ++in_brackets;
            break ;
        }
    }
    if (in_brackets != 1)
    {
        std::cerr << "Error: Missing brackets" << std::endl;
        exit(EXIT_FAILURE);
    }
	while (std::getline(file, line))
	{
		if (line[0] == '#')
			continue ;
		if (line.find("}") != std::string::npos)
        {
			std::cout << "Server setup done" << std::endl;
            _servers.push_back(serv);
			return (1);
        }
		if (line.find("server_name") != std::string::npos)
			serv_name_setter(serv, line);
		// if (line.find("listen") != std::string::npos)
		// 	serv.set_port(std::atoi(line.substr(line.find("listen")
		// 				+ 7).c_str()));
		// if (line.find("root") != std::string::npos)
		// 	serv.set_root(line.substr(line.find("root") + 5));
		// if (line.find("error_page") != std::string::npos)
		// 	serv.set_error_page(line.substr(line.find("error_page") + 11));
		// if (line.find("size_limit") != std::string::npos)
		// 	serv.set_size_limit(std::atoi(line.substr(line.find("size_limit")
		// 				+ 11).c_str()));
	}
	std::cout << "Missing brackets" << std::endl;
	return (false);
}

bool Config::parse_config(std::string path)
{
	

	if (path.empty())
	{
		std::cerr << "Error: No path to config file" << std::endl;
		return (false);
	}
	std::ifstream file(path.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: Can't open config file" << std::endl;
		return (false);
	}
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
			continue ;
		if (line[0] == '#')
			continue ;
		if (line.find("server") != std::string::npos)
		{
			Server serv;
			setup_server(serv, file);
			std::cout << serv.get_server_name() << std::endl;
			_servers.push_back(serv);
			std::cout << _servers.size() << std::endl;
			std::cout << _servers[0].get_server_name() << std::endl;
		}
	}
	file.close();
    return (true);
}
