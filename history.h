#pragma once

#include "defines.h"
#include "log.h"

extern char historyPath[PATH_MAX];

extern int historyStart;
extern int historyLen;
extern char historyData[HISTORY_LEN][COMMAND_MAX];

void loadHistory();

void updateHistory(char* command);

void writeHistory();