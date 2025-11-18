#include "commands.h"

static char prevDir[PATH_MAX];

void echo(char** argv)
{
    int argc = 1;
    while(argv[argc] != NULL)
    {
        printf("%s ",argv[argc++]);
    }
    printf("\n");
}

void pwd()
{
    char cwd[PATH_MAX];
    getcwd(cwd,sizeof(cwd));

    printf("%s\n",cwd);
}

void changeDir(char** argv,char * cwd,char* homedir)
{
    int argc = 1;

    if(argv[argc] != NULL)
    {
        char path[PATH_MAX];
        strcpy(path,argv[argc++]);

        if(argv[argc]!=NULL)
        {
            perror("Too Many Arguments");
            return;
        }

        const char* prevDirSym = "-";

        if(strcmp(path,prevDirSym) == 0)
        {
            logMessage("- mentioned in cd, Size of Previous Directory: %d\n",strlen(prevDir));

            if(strlen(prevDir) == 0)
            {
                perror("No Previous Directory");
                return;
            }
            else
            {
                strcpy(path,prevDir);
            }
        }

        subTildetoHome(path,homedir);

        logMessage("Path Specified in cd: %s\n",path);
        
        int cdCode = chdir(path);
        
        logMessage("cd Code Returned: %d\n",cdCode);
        
        if(cdCode == -1)
        {
            printf("%s: No such directory\n",path);
        }
        else if(cdCode == 0)
        {
            strcpy(prevDir,cwd);
        }
        else
        {
            perror("Error while changing directory");
        }
    }
    else
    {
        logMessage("No Path Specified Defaulting to home dir\n");
        chdir(homedir);
        strcpy(prevDir,homedir);
    }
}

void getHistory()
{
    char* token = strtok(NULL,DELIMITERS);

    if(token != NULL)
    {
        printf("Too Many Arguments\n");
        return;
    }

    for(int i=MAX(0,historyLen - HISTORY_DISPLAY);i<historyLen;i++)
    {
        printf("%s\n",historyData[(i + historyStart)%HISTORY_LEN]);
    }
}