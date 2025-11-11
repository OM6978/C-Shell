#include "utils.h"
#include "log.h"

int isPrefix(char* path,char* homedir)
{
    int clen = strlen(path);
    int hlen = strlen(homedir);

    if(hlen > clen)return 0;

    for(int i=0;i<hlen;i++)
    {
        if(path[i] != homedir[i])
            return 0;
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

int splitArgs(char** argv,char* command,char** inputFile,char** outputFile)
{
    int argc = 0;
    char* token = strtok(command,DELIMITERS);

    const char* inputSym = "<";
    const char* outputSym = ">";
    
    while(token != NULL)
    {
        if(argc == MAX_ARGS-1)
        {
            perror("Argument Limit Exceeded");
        }

        if(strcmp(token,inputSym) == 0 && *inputFile == NULL)
        {
            logMessage("Input Redirection Detected\n");

            token = strtok(NULL,DELIMITERS);

            if(token == NULL)
            {
                perror("Syntax error near token <");
                return -1;
            }

            *inputFile = token;

            logMessage("Input file specified: %s\n",*inputFile);
        }
        else if(strcmp(token,outputSym) == 0 && *outputFile == NULL)
        {
            logMessage("Output Redirection Detected\n");

            token = strtok(NULL,DELIMITERS);

            if(token == NULL)
            {
                perror("Syntax error near token >");
                return -1;
            }

            *outputFile = token;

            logMessage("Output file specified: %s\n",*outputFile);
        }
        else argv[argc++] = token;

        token = strtok(NULL,DELIMITERS);
    }

    argv[argc] = NULL;

    return argc;
}