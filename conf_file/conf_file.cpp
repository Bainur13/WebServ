#include "conf_file.hpp"

Config::Config()
{
}

Config::Config(std::string path)
{
	_file.open(path.c_str());
	if (!_file.is_open())
	{
		std::cerr << "Path: " << path << std::endl;	
		std::cerr << "Error: Can't open config file" << std::endl;
		exit(EXIT_FAILURE);
	}
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

std::ifstream &Config::get_file()
{
	return (_file);
}

void Config::error_put_config(std::string error)
{
	std::cerr << error << std::endl;
	_file.close();
	exit(EXIT_FAILURE);
}

std::string Config::parse_ascii_setter(std::string line, std::string to_search)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	if ((int)line.find(to_search) != i)
		error_put_config(to_search + " error");
	i = line.find(to_search) + to_search.size();
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	if (line[i] == ';')
		error_put_config("empty " + to_search);
	j = i;
	while (isalnum(line[i]) || line[i] == '.' || line[i] == '-'
		|| line[i] == '_' || line[i] == '/')
		++i;
	if (line[i] != ';' || line[i + 1] != '\0')
		error_put_config(to_search + " error");
	return (line.substr(j, i - j));
}

int	Config::parse_int_setter(std::string line, std::string to_search)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	if ((int)line.find(to_search) != i)
		error_put_config(to_search + " error");
	i = line.find(to_search) + to_search.size();
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	if (line[i] == ';')
		error_put_config("empty " + to_search);
	j = i;
	while (isdigit(line[i]))
		++i;
	if (line[i] != ';' || line[i + 1] != '\0')
		error_put_config(to_search + " error");
	return (std::atoi(line.substr(j, i - j).c_str()));
}

void	Config::is_valid_line(std::string line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	if (line[i] != '\0')
		error_put_config("Unknown command");
	return ;
}

bool Config::unique_symbol(std::string line, char c)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	if (line[i] != c)
		error_put_config("Error : Missing " + std::string(1, c));
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	if (line[i + 1] != '\0')
		error_put_config(std::string(1, c) + " need to be unique on the line");
	return (true);
}

void Config::parse_error_page(std::string line, std::string to_search, Server &serv)
{
	int	i;
	int	j;
	int	code;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	if ((int)line.find(to_search) != i)
		error_put_config(to_search + " error");	
	i = line.find(to_search) + to_search.size();
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	if (line[i] == ';')
		error_put_config("empty " + to_search);
	j = i;
	while (isdigit(line[i]))
		++i;
	if (line[i] != ' ')
		error_put_config(to_search + " error");
	code = std::atoi(line.substr(j, i - j).c_str());
	while (line[i] == ' ' || line[i] == '\t')
		++i;
	if (line[i] == ';')
		error_put_config("empty " + to_search);
	j = i;
	while (isalnum(line[i]) || line[i] == '.' || line[i] == '-'
		|| line[i] == '_' || line[i] == '/')
		++i;
	if (line[i] != ';' || line[i + 1] != '\0')
		error_put_config(to_search + " error");
	serv.set_error_page(code, line.substr(j, i - j));
}



bool Config::setup_server(Server &serv, std::ifstream &file)
{
	int	in_brackets;

	std::string line;
	in_brackets = 0;
	while (std::getline(file, line))
	{
		if (line == "{")
		{
			++in_brackets;
			break ;
		}
	}
	if (in_brackets != 1)
		error_put_config("Error: Missing brackets");
	while (std::getline(file, line))
	{
		if (line[0] == '#')
			continue ;
		else if ((line.find("}") != std::string::npos) && unique_symbol(line, '}'))
		{
			std::cout << "Server setup done" << std::endl;
			return (1);
		}
		else if (line.find("server_name") != std::string::npos)
			serv.set_server_name(parse_ascii_setter(line, "server_name"));
		else if (line.find("listen") != std::string::npos)
			serv.set_port(parse_int_setter(line, "listen"));
		else if (line.find("root") != std::string::npos)
			serv.set_root(parse_ascii_setter(line, "root"));
		else if (line.find("error_page") != std::string::npos)
			parse_error_page(line, "error_page", serv);
		else if (line.find("size_limit") != std::string::npos)
			serv.set_size_limit(parse_int_setter(line, "size_limit"));
		else
			is_valid_line(line);
	}
	std::cout << "Missing brackets" << std::endl;
	return (false);
}

bool Config::parse_config()
{
	Server serv;

	if (!_file.is_open())
	{
		std::cerr << "Error: No file" << std::endl;
		return (EXIT_FAILURE);
	}
	std::string line;
	while (std::getline(_file, line))
	{
		if (line.empty())
			continue ;
		if (line[0] == '#')
			continue ;
		if (line.find("server") != std::string::npos)
		{
			if (setup_server(serv, _file))
				_servers.push_back(serv);
		}
	}
	_file.close();
	return (true);
}
