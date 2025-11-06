#include "defines.h"
#include "log.h"
#include "commands.h"
#include "utils.h"

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

    char command[COMMAND_MAX];

    while(1)
    {
        printf(BOLD_LIME_GREEN);
        printf("<%s@%s:%s> ",username,hostname,cwd);
        printf(ANSI_COLOR_RESET);

        fgets(command,sizeof(command),stdin);
        int cmdlen = strlen(command);

        command[cmdlen-1] = '\0';

        updateHistory(command);

        char* shellcmd = strtok(command, delimiters);

        logString(2,"Shell Command :",shellcmd);

        if(strcmp(shellcmd,allCommands[0]) == 0)
        {            
            echo();
        }
        else if(strcmp(shellcmd,allCommands[1]) == 0)
        {
            pwd();
        }
        else if(strcmp(shellcmd,allCommands[2]) == 0)
        {
            changeDir(cwd,homedir);
            updateCWD(cwd,homedir,sizeof(cwd));
        }
        else if(strcmp(shellcmd,allCommands[3]) == 0)
        {
            getHistory();
        }
        else if(strcmp(shellcmd,allCommands[4]) == 0)
        {
            logString(1,"Exiting");
            break;
        }
        else
        {
            printf("Unknown Command : %s\n",shellcmd);
        }
    }

    logDest();

    return 0;
}