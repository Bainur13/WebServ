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
	std::string _interpreterPath;
	int _cgiPid;
	int _cgiFdToRead;
	std::string _cgiMethod;

  public:
	Cgi();
	~Cgi();
	Cgi(const Cgi &copy);
	Cgi(std::string path, std::string interpreter);

	Cgi &operator=(const Cgi &copy);

	void setPath(std::string path);
	void setInterpreter(std::string interpreter);
	void setMethod(std::string method);

	std::string getPath();
	std::string getMethod();
	std::string getInterpreter();
	int getCgiPid();
	int getCgiFd();
	std::vector<const char*> build_env(Request &request);

	bool executeCgi(Request &request);
};

#include "Request.hpp"

#endif
