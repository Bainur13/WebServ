#ifndef CGI_HPP
#define CGI_HPP

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>
#include <vector>
class Request;

class Cgi
{
  private:
	std::string _scriptPath;
	int _cgiPid;
	int _cgiFdToRead;
	int _clientFd;
	std::string _cgiMethod;

  public:
	Cgi();
	~Cgi();
	Cgi(const Cgi &copy);
	Cgi(std::string path);

	Cgi &operator=(const Cgi &copy);

	void setPath(std::string path);
	void setInterpreter(std::string interpreter);
	void setMethod(std::string method);
	void setClientFd(int client_fd);

	std::string getPath();
	std::string getMethod();
	std::string getInterpreter();
	int getCgiPid();
	int getCgiFd();
	int getClientFd();
	std::vector<const char*> build_env(Request &request);

	bool executeGetCgi(Request &request);
	bool executePostCgi(Request &request);
	Cgi *clone();
};

#include "Request.hpp"

#endif
