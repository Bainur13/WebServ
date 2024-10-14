#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "conf.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage: ./webserver <port>" << std::endl;
		return (1);
	}
    Conf conf(av[1]);
}
