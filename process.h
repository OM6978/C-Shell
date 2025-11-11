#include "defines.h"
#include "utils.h"

extern pid_t foregroundPID;

void handleSIGCHLD(int sig);

void executeStandaloneCommand(char** argv,char* inputFile,char* outputFile,int foreground);