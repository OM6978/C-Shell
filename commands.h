#pragma once

#include "defines.h"

static const char* delimiters = " \t";

static const char *allCommands[] = {
        "echo",
        "pwd",
        "cd",
        "history",
        "exit"
    };

static char prevDir[PATH_MAX];

void echo();

void pwd();

void changeDir(char * cwd,char* homedir);

void getHistory();