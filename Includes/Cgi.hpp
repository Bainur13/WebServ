#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>
#include <vector>

class Cgi
{
  private:
	std::string _scriptPath;
	std::string _interpreterPath;

  public:
	Cgi(const Cgi &copy);
	Cgi &operator=(const Cgi &copy);
	Cgi(std::string path, std::string interpreter);
	void setPath(std::string path);
	std::string getPath();
	void setInterpreter(std::string interpreter);
	std::string getInterpreter();
	bool executeCgi(std::vector<std::string> argsToPass);
	~Cgi();
};
