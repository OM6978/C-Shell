#include "commands.h"

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
            printf("Too Many Arguments\n");
            return;
        }

        const char* prevDirSym = "-";

        if(strcmp(path,prevDirSym) == 0)
        {
            logString(2,"- mentioned in cd,","Size of Previous Directory:");
            logInteger(strlen(prevDir));

            if(strlen(prevDir) == 0)
            {
                printf("No Previous Directory\n");
                return;
            }
            else
            {
                strcpy(path,prevDir);
            }
        }

        subTildetoHome(path,homedir);

        logString(2,"Path Specified in cd:",path);
        
        int cdCode = chdir(path);
        
        logString(1,"cd Code Returned:");
        logInteger(cdCode);
        
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
        logString(1,"No Path Specified Defaulting to home dir");
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