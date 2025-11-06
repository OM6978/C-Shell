#pragma once

#include "defines.h"

extern const char* historyPath;

extern int historyStart;
extern int historyLen;
extern char historyData[HISTORY_LEN][COMMAND_MAX];

int isPrefix(char* cwd,char* homedir);

void updateCWD(char* cwd,char* homedir,size_t size);

void subHomeToTilde(char* path,char* homedir);

void subTildetoHome(char* path,char* homedir);

int splitArgs(char** argv,char* command);

void loadHistory();

void updateHistory(char* command);

void writeHistory();