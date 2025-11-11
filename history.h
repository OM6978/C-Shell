#pragma once

#include "defines.h"
#include "log.h"

extern const char* historyPath;

extern int historyStart;
extern int historyLen;
extern char historyData[HISTORY_LEN][COMMAND_MAX];

void loadHistory();

void updateHistory(char* command);

void writeHistory();