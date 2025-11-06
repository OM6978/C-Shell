#include "commands.h"
#include "utils.h"
#include "log.h"

void echo()
{
    char* token = strtok(NULL,delimiters);

    while(token != NULL)
    {
        printf("%s ",token);
        token = strtok(NULL,delimiters);
    }
    printf("\n");
}

void pwd()
{
    char cwd[PATH_MAX];
    getcwd(cwd,sizeof(cwd));

    printf("%s\n",cwd);
}

void changeDir(char * cwd,char* homedir)
{
    char* token = strtok(NULL,delimiters);

    if(token != NULL)
    {
        char path[PATH_MAX];
        strcpy(path,token);

        token = strtok(NULL,delimiters);

        if(token!=NULL)
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
        
        if(cdCode != 0)
        {
            printf("%s: No such directory\n",path);
        }
        else
        {
            strcpy(prevDir,cwd);
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
    char* token = strtok(NULL,delimiters);

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

void writeHistory()
{
    FILE* historyFile = fopen(historyPath,"w");
    for(int i=0;historyLen;i++)
    {
        fprintf(historyFile,"%s\n",historyData[(i+historyStart)%HISTORY_LEN]);
    }

    fclose(historyFile);
}