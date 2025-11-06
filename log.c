#include "log.h"

void logInit()
{
    FILE* logPtr = fopen(LOG_FILE,"a");

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(logPtr,"---------- [Session Date and Time: %02d/%02d/%04d %02d:%02d:%02d] ----------\n",
        t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
        t->tm_hour, t->tm_min, t->tm_sec);

    fprintf(logPtr,"\n");

    fclose(logPtr);
}

void logString(int num_args, ...)
{
    if(num_args == 0)return;

    FILE* logPtr = fopen(LOG_FILE,"a");
    
    va_list args;
    const char *current_string;
    int count = 0;
    
    va_start(args, num_args);

    for(int i=0;i<num_args-1;i++)
    {
        current_string = va_arg(args, const char *);
        fprintf(logPtr,"%s ", current_string);
    }

    current_string = va_arg(args, const char *);
    fprintf(logPtr,"%s", current_string);
    
    va_end(args);

    fprintf(logPtr,"\n");

    fclose(logPtr);
}

void logInteger(int x)
{
    FILE* logPtr = fopen(LOG_FILE,"a");
    fprintf(logPtr,"%d\n",x);
    fclose(logPtr);
}

void logDest()
{
    FILE* logPtr = fopen(LOG_FILE,"a");
    fprintf(logPtr,"\n");
    fclose(logPtr);
}