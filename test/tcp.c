#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int server_fd;
    int listen_to;
    struct sockaddr_in address;
    int new_socket;
    int addrlen;
    int opt = 1;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Socket Failed");
        return 0;
    }

    // Set socket options to reuse address and port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        return 0;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind Failed");
        return 0;
    }

    addrlen = sizeof(address);
    listen_to = listen(server_fd, 10);
    if (listen_to < 0)
    {
        perror("Listen Failed");
        return 0;
    }

    while (1)
    {
        // Accept incoming connections
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0)
        {
            perror("Accept Failed");
            return 0;
        }
        char buffer[1000];
        int value = read(new_socket, buffer, 1000);
        buffer[value] = '\0';
        printf("%s\n", buffer);
        close(new_socket);
        // Handle the new connection
    }

    return 0;
}
