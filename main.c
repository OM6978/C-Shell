#include "defines.h"
#include "log.h"
#include "commands.h"
#include "utils.h"
#include "process.h"

int main()
{
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
        printf(BOLD_LIME_GREEN);
        printf("<%s@%s:%s> ",username,hostname,cwd);
        printf(ANSI_COLOR_RESET);
        
        fgets(command,sizeof(command),stdin);
        int cmdlen = strlen(command);
        command[--cmdlen] = 0;

        updateHistory(command);

        int argc = splitArgs(argv,command);

        if(argc == 0)continue;

        logString(2,"Shell Command :",argv[0]);

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
            logString(1,"Exiting");
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
                
                executeStandaloneCommand(argv,0);
            }
            else
            executeStandaloneCommand(argv,1);
        }

        updateCWD(cwd,homedir,sizeof(cwd));
    }

    writeHistory();

    logDest();

    return 0;
}