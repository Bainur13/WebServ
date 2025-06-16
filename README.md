
---
# webserv – HTTP Server in C++

## Description

**webserv** is a lightweight HTTP/1.1 web server written in C++.  
It handles multiple client connections using non-blocking sockets and multiplexing (poll/epoll), supports GET, POST, and DELETE methods, and allows for static file serving and CGI execution.  
Bonus features include load balancing, persistent connections, and advanced error handling.

## Features

- HTTP/1.1 protocol compliance
- Handling of GET, POST, DELETE requests
- Static file serving and directory listing
- CGI support (Python/PHP scripts execution)
- Configurable via `.conf` files (custom server directives)
- Error handling with custom error pages
- Connection multiplexing via `poll()` (or `epoll`/`kqueue` depending on OS)
- Persistent connections (keep-alive) (bonus)
- Load balancing across multiple servers (bonus)
- Large file support and chunked transfer encoding (bonus)

## Skills & Concepts Practiced

✔️ Network programming in C++ (sockets, non-blocking I/O)  
✔️ HTTP/1.1 protocol design and request parsing  
✔️ CGI execution flow (child process management)  
✔️ Poll-based I/O multiplexing  
✔️ Configuration file parsing  
✔️ Exception handling and resource management in C++  
✔️ Performance tuning and scalability considerations  

## Why this project matters

`webserv` is a complete backend server project, offering insight into how modern web servers (like Nginx or Apache) are built.  
This project is valuable for understanding networking, protocol design, server architecture, and performance optimization.

## Project Status

✅ Completed with 125% score (including bonus)

## Usage Example

```bash
./webserv config/example.conf
