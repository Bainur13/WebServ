// Client side C/C++ program to demonstrate Socket programming
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int	main(int argc, char const *argv[])
{
	int					sock;
	int					server_fd;
    int                 new_socket;
    int					opt = 1;
	struct sockaddr_in	address;
    int					addrlen = sizeof(address);
	long				valread;
	struct sockaddr_in	serv_addr;
	char				*hello;
	char				buffer[1024] = {0};

	sock = 0;
	hello = "Hello from client";
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == 0)
	{
		perror("Socket failed");
		return (1);
	}
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		return (1);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("Bind failed");
		return (1);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("Listen failed");
		return (1);
	}
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		close(server_fd);
		printf("\n Socket creation error \n");
		return (-1);
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(4221);
	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		close(server_fd);
		close(sock);
		printf("\nInvalid address/ Address not supported \n");
		return (-1);
	}
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return (-1);
	}
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0)
    {
        perror("Accept failed");
        return 1;
    }
    valread = read(new_socket, buffer, 1024);
    buffer[valread] = '\0';
    printf("Message received: %s\n", buffer);
	send(sock, hello, strlen(hello), 0);
	printf("Hello message sent\n");
	valread = read(sock, buffer, 1024);
	buffer[valread] = '\0';
	printf("%s\n", buffer);
    close(server_fd);
    close(sock);
    close(new_socket);
	return (0);
}
