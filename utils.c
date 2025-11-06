#include "utils.h"

const char* historyPath = "/home/om/Acads/C-Shell/history.txt";

int historyStart = 0;
int historyLen = 0;
char historyData[HISTORY_LEN][COMMAND_MAX];

int isPrefix(char* path,char* homedir)
{
    int clen = strlen(path);
    int hlen = strlen(homedir);

    if(hlen > clen)return 0;

    for(int i=0;i<hlen;i++)
    {
        if(path[i] != homedir[i])
        {
            return 0;
        }
    }

    return 1;
}

void updateCWD(char* cwd,char* homedir,size_t size)
{
    getcwd(cwd,size);
    subHomeToTilde(cwd,homedir);
}

void subHomeToTilde(char* path,char* homedir)
{
    if(isPrefix(path,homedir))
    {
        char temp[PATH_MAX];
        strcpy(temp,path);
    
        int tmplen = strlen(temp);
    
        path[0] = '~';
        int clen = 1;
    
        for(int i=strlen(homedir);i<tmplen;i++)
        {
            path[clen++] = temp[i];
        }
    
        path[clen] = '\0';
    }
}

void subTildetoHome(char* path,char* homedir)
{
    int hlen = strlen(homedir);

    char temp[PATH_MAX];
    strcpy(temp,path);

    int tmplen = strlen(temp);

    int plen = 0;

    for(int i=0;i<tmplen;i++)
    {
        if(temp[i] == '~')
        {
            for(int j=0;j<hlen;j++)
            {
                path[plen++] = homedir[j];
            }
        }
        else
        {
            path[plen++] = temp[i];
        }
    }

    path[plen] = '\0';
}

void updateHistory(char* command)
{
    if(historyLen == HISTORY_LEN)
    {
        strcpy(historyData[historyStart++],command);
        historyStart%=HISTORY_LEN;
    }
    else
    {
        strcpy(historyData[historyLen++],command);
    }
}