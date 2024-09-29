#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <arpa/inet.h>
# include <cstdlib>
# include <cstring>
# include <errno.h>
# include <iostream>
# include <map>
# include <netdb.h>
# include <string>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>

class Response
{
  private:
	std::map<std::string, std::string> _line;
	std::map<std::string, std::string> _header;
	std::string _body;

  public:
    Response();
    Response(Response const &src);
    ~Response();

    Response &operator=(Response const &src);
    std::string final_response();
    void set_line(std::string key, std::string value);
    void set_header(std::string key, std::string value);
    void set_body(std::string body);
};

#endif
