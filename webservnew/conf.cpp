#include "conf.hpp"


Conf::Conf()
{
}

Conf::Conf(const std::string &filename)
{
	std::ifstream file;
	std::string line;
	file.open(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file" << std::endl;
		exit(EXIT_FAILURE);
	}
	while (std::getline(file, line))
	{
		if (is_empty(line))
			continue ;
		else if (is_server(line, file))
			_servers.push_back(parse_server(file));
		else
			error_exit("Error: invalid file");
	}
	file.close();
}

Server Conf::parse_server(std::ifstream &file)
{
	Server	server;
	int		i;

	std::string line;
	std::vector<std::string> line_s;
	i = 0;
	while (std::getline(file, line))
	{
		line_s = split_line(line, " ");
		if (line_s.size() == 0)
			continue ;
		if (unique_symbol(line_s, "}"))
			break ;
		if (line_s[0] == "server_name")
			server.set_server_name(line_s);
		else if (line_s[0] == "root")
			server.set_root(line_s);
		else if (line_s[0] == "size_limit")
			server.set_sizelimit(line_s);
		else if (line_s[0] == "listen")
			server.set_listen(line_s);
		else if (line_s[0] == "error_page")
			server.set_error_page(line_s);
		else if (line_s[0] == "index")
			server.set_index(line_s);
		else if (line_s[0] == "method")
			server.set_method(line_s);
		else
			error_exit("Error: invalid server");
	}
	std::cout << "Server name: " << server.get_server_name() << std::endl;
	std::cout << "Root: " << server.get_root() << std::endl;
	std::cout << "Size limit: " << server.get_sizelimit() << std::endl;
	std::cout << "Host: " << server.get_host() << std::endl;
	std::cout << "Port: " << server.get_port() << std::endl;
	std::cout << "Error page: " << server.get_error_page(404) << std::endl;
	std::cout << "Index: " << server.get_index() << std::endl;
	std::vector <std::string> method = server.get_method();
	for (size_t i = 0; i < method.size(); i++)
		std::cout << "Method: " << method[i] << std::endl;
	return (server);
}

Conf::Conf(const Conf &copy)
{
	*this = copy;
}

Conf &Conf::operator=(const Conf &copy)
{
	if (this != &copy)
	{
	}
	return (*this);
}

Conf::~Conf()
{
}
