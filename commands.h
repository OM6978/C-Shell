#pragma once

#include "defines.h"
#include "utils.h"
#include "history.h"
#include "log.h"

static const char *allCommands[] = {
        "echo",
        "pwd",
        "cd",
        "history",
        "exit"
    };

void echo(char** argv);

void pwd();

void changeDir(char** argv,char * cwd,char* homedir);

void getHistory();