#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <string>
#include <unistd.h>

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

std::string read_fd_to_end(int fd)
{
	char	buffer[1024];
	int		valread;

	std::string result;
	result = "";
	while (1)
	{
		valread = read(fd, buffer, 1024);
		if (valread <= 0)
		{
			std::cerr << "Error of read / Nothing to read from fd" << std::endl;
			break ;
		}
		buffer[valread] = '\0';
		result += buffer;
		ft_bzero(buffer, 1024);
		if (valread < 1024)
			break ;
	}
	return (result);
}
