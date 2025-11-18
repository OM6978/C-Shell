#include "history.h"

char historyPath[PATH_MAX];

int historyStart = 0;
int historyLen = 0;
char historyData[HISTORY_LEN][COMMAND_MAX];

void loadHistory()
{
    FILE *historyFile = fopen(historyPath, "r");
    
    if(historyFile == NULL)return;

    char buffer[COMMAND_MAX];

    while(fgets(buffer, COMMAND_MAX, historyFile) != NULL && historyLen < HISTORY_LEN)
    {
        buffer[strcspn(buffer, "\n")] = 0; 
        
        strcpy(historyData[historyLen++], buffer);
    }

    fclose(historyFile);
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

void writeHistory()
{
    FILE* historyFile = fopen(historyPath,"w");

    for(int i=0;i<historyLen;i++)
    {
        fprintf(historyFile,"%s\n",historyData[(i+historyStart)%HISTORY_LEN]);
    }

    fclose(historyFile);
}