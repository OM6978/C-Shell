#include "defines.h"
#include "log.h"
#include "commands.h"
#include "utils.h"
#include "process.h"
#include "history.h"

void handleSIGINT(int sig)
{
    if(foregroundPID > 0)
    {
        int pidRes = kill(foregroundPID, SIGINT);
        logMessage("Foreground Process Exited with Code: %d\n",pidRes);
    }
}

void shellPrompt(char* username,char* hostname,char* cwd)
{
    printf(BOLD_LIME_GREEN);
    printf("<%s@%s:%s> ",username,hostname,cwd);
    printf(ANSI_COLOR_RESET);
}

int main()
{
    signal(SIGINT, handleSIGINT);
    signal(SIGCHLD, handleSIGCHLD);

    logInit();

    char cwd[PATH_MAX];
    char hostname[H_NAME_MAX];

    getcwd(cwd,sizeof(cwd));
    gethostname(hostname,sizeof(hostname));

    uid_t uid = getuid(); 
    struct passwd *pw = getpwuid(uid);

    char* homedir = pw->pw_dir;
    char* username = pw->pw_name;

    subHomeToTilde(cwd,homedir);

    loadHistory();

    char command[COMMAND_MAX];
    char *argv[MAX_ARGS];
    
    while(1)
    {
        shellPrompt(username,hostname,cwd);
        
        if(fgets(command,sizeof(command),stdin) == NULL) 
        {
            printf("\n");
            logMessage("Exiting due to EOF (Ctrl+D) \n");
            break;
        }

        int cmdlen = strlen(command);
        command[--cmdlen] = 0;

        updateHistory(command);

        char* inputFile = NULL;
        char* outputFile = NULL;

        int argc = splitArgs(argv,command,&inputFile,&outputFile);

        if(argc <= 0)continue;

        // logArgs(argv);

        logMessage("Shell Command : %s\n",argv[0]);

        if(strcmp(argv[0],allCommands[0]) == 0)
        {            
            echo(argv);
        }
        else if(strcmp(argv[0],allCommands[1]) == 0)
        {
            pwd();
        }
        else if(strcmp(argv[0],allCommands[2]) == 0)
        {
            changeDir(argv,cwd,homedir);
        }
        else if(strcmp(argv[0],allCommands[3]) == 0)
        {
            getHistory();
        }
        else if(strcmp(argv[0],allCommands[4]) == 0)
        {
            logMessage("Exiting\n");
            break;
        }
        else
        {
            int rarglen = strlen(argv[argc-1]);     // Length of Last Argument
            if(argv[argc-1][rarglen-1] == '&')
            {
                if(rarglen == 1)
                    argv[--argc] = NULL;
                else
                    argv[argc-1][--rarglen] = '\0';
                
                executeStandaloneCommand(argv,inputFile,outputFile,0);
            }
            else
                executeStandaloneCommand(argv,inputFile,outputFile,1);
        }

        updateCWD(cwd,homedir,sizeof(cwd));
    }

    writeHistory();

    logDest();

    return 0;
}