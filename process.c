#include "process.h"

void executeStandaloneCommand(char** argv,int foreground)
{
    pid_t pid, wpid;
    int status;

    pid = fork();

    if(pid == 0)       // CHILD PROCESS
    {
        if(execvp(argv[0], argv) == -1)
        {
            perror("Failed to execute foreground process");
            exit(EXIT_FAILURE);
        }
    }
    else if(pid < 0)
    {
        perror("Process Fork Failed");
    }
    else if(foreground)
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        }
        while (!WIFEXITED(status) && !WIFSIGNALED(status)); 
    }
}