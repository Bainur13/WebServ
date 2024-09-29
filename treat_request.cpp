#include "webServ.hpp"

Response treat_request(Request req)
{
    Response res;
    int file_fd;

    res.set_line("Version", "HTTP/1.1");
    if (req.get_request_line("Method") == "GET")
    {
        std::string path = req.get_request_line("Path");
        if (path == "/")
        {
            res.set_line("Status", "200");
            res.set_line("Reason", "OK");
            path = "./index/index.html";
            res.set_header("Content-Type", "text/html");
        }
        else
        {
            res.set_line("Status", "404");
            res.set_line("Reason", "Not Found");
            path = "./index/404.html";
            res.set_header("Content-Type", "text/html");
        }
        file_fd = open(path.c_str(), O_RDONLY);
        if (file_fd < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            exit(EXIT_FAILURE);
        }
        res.set_body(read_fd_to_end(file_fd));
    }
    else
    {
        res.set_line("Status", "405");
        res.set_line("Reason", "Method Not Allowed");
        res.set_header("Content-Type", "text/html");
        res.set_body("<html><body><h1>405 Method Not Allowed</h1></body></html>");
    }
    return res;
}
