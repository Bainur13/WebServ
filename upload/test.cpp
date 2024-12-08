#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <string>

int main(void)
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1)
    {
        perror("Erreur creating pipe");
        return 1;
    }

    pid = fork();
    if (pid == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        std::vector<const char*> argv;
        argv.push_back("/home/vda-conc/env.py");
        argv.push_back(NULL);

        const char* envp[] = {"TEST_ENV=Hello", "TALAN=BB", NULL};
        if (execve("/home/vda-conc/env.py", const_cast<char* const*>(argv.data()), const_cast<char* const*>(envp)) == -1)
        {
            perror("Erreur lors de l'exécution du script");
            _exit(1);
        }
    }
    else if (pid > 0)
    {
        close(pipefd[1]);

        char buffer[1024];
        ssize_t bytesRead;

        std::string output;

        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0)
        {
            buffer[bytesRead] = '\0';
            output += buffer;
        }

        close(pipefd[0]);

        int status;
        waitpid(pid, &status, 0);

        std::cout << "Script output:\n" << output << std::endl;

        if (WIFEXITED(status))
        {
            int exitCode = WEXITSTATUS(status);
            std::cout << "Script exited with code: " << exitCode << std::endl;
        }
        else
        {
            std::cerr << "Le script n'a pas terminé correctement." << std::endl;
        }
    }
    else
    {
        perror("Erreur lors du fork");
        return 1;
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <string>

int main(void)
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1)
    {
        perror("Erreur creating pipe");
        return 1;
    }

    pid = fork();
    if (pid == 0) 
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        std::vector<const char*> argv;
        argv.push_back("/home/vda-conc/env.py");
        argv.push_back(NULL);

        const char* envp[] = {"TEST_ENV=Hello", "TALAN=BB", NULL};
        if (execve("/home/vda-conc/env.py", const_cast<char* const*>(argv.data()), const_cast<char* const*>(envp)) == -1)
        {
            perror("Erreur lors de l'exécution du script");
            _exit(1);
        }
    }
    else if (pid > 0)
    {
        close(pipefd[1]);

        char buffer[1024];
        ssize_t bytesRead;

        std::string output;

        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0)
        {
            buffer[bytesRead] = '\0';
            output += buffer;
        }

        close(pipefd[0]);

        int status;
        waitpid(pid, &status, 0);

        std::cout << "Script output:\n" << output << std::endl;

        if (WIFEXITED(status))
        {
            int exitCode = WEXITSTATUS(status);
            std::cout << "Script exited with code: " << exitCode << std::endl;
        }
        else
        {
            std::cerr << "Le script n'a pas terminé correctement." << std::endl;
        }
    }
    else
    {
        perror("Erreur lors du fork");
        return 1;
    }

    return 0;
}
