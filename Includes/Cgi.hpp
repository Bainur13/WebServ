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

  public:
	Cgi();
	Cgi(const Cgi &copy);
	Cgi &operator=(const Cgi &copy);
	Cgi(std::string path, std::string interpreter);
	void setPath(std::string path);
	std::string getPath();
	void setInterpreter(std::string interpreter);
	std::string getInterpreter();
	bool executeCgi(std::string &cgiOutput, Request &request);
	std::vector<const char*> build_env(Request &request);
	~Cgi();
};

#include "Request.hpp"

#endif
