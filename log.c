#include "defines.h"
#include "log.h"

char logPath[PATH_MAX];

static FILE* logPtr;

void logInit()
{
    logPtr = fopen(logPath,"a");

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(logPtr,"---------- [Session Date and Time: %02d/%02d/%04d %02d:%02d:%02d] ----------\n",
        t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
        t->tm_hour, t->tm_min, t->tm_sec);

    fprintf(logPtr,"\n");
    fflush(logPtr);
}

void logMessage(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    vfprintf(logPtr, format, args);
    
    va_end(args);
    
    if (format[strlen(format) - 1] != '\n') {
        fprintf(logPtr, "\n");
    }
    fflush(logPtr);
}

void logArgs(char ** argv)
{
    int argc = 0;
    while(argv[argc] != NULL)
    {
        logMessage("%s ",argv[argc++]);
    }
}

void logDest()
{
    if(logPtr == NULL)return;

    fprintf(logPtr,"\n");
    fclose(logPtr);
}