#include <iostream>
#include <string>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <cstdlib>

void ft_bzero(void *s, size_t n)
{
    char *str = (char *)s;
    size_t i = 0;

    while (i < n)
    {
        str[i] = '\0';
        i++;
    }
}

std::string read_fd_to_end(int fd)
{
    std::string result;
    char buffer[1024];
    int valread;

    while (1)
    {
        valread = read(fd, buffer, 1024);;
        if (valread == 0)
            break;
        if (valread < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(EXIT_FAILURE);
        }
        buffer[valread] = '\0';
        result += buffer;
        ft_bzero(buffer, 1024);
        if (valread < 1024)
            break;
    }
    return result;
}
