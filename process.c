#include "process.h"
#include "log.h"

pid_t foregroundPID = -1;

void handleSIGCHLD(int sig)
{
    pid_t pid;
    int status;
    
    while ((pid = waitpid((pid_t)-1, &status, WNOHANG)) > 0)
    {
        const char msg[] = "\n[Shell] Background job reaped.\n";
        write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    }
}

void executeStandaloneCommand(char** argv,char* inputFile,char* outputFile,int foreground)
{
    pid_t pid;
    int status;

    pid = fork();

    if(pid == 0)       // CHILD PROCESS
    {        
        if(inputFile != NULL)
        {
            int in = open(inputFile, O_RDONLY);
            if(in < 0)
            {
                perror("Error opening input file");
            }

            dup2(in, STDIN_FILENO);
            close(in);
        }

        if(outputFile != NULL)
        {
            int outFD = creat(outputFile, 0644);
            dup2(outFD, STDOUT_FILENO);
            close(outFD);
        }

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
        foregroundPID = pid;
        
        pid_t wpid;

        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        }
        while (!WIFEXITED(status) && !WIFSIGNALED(status)); 

        foregroundPID = -1;
    }
}