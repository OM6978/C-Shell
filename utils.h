#pragma once

#include "defines.h"

int isPrefix(char* cwd,char* homedir);

void updateCWD(char* cwd,char* homedir,size_t size);

void subHomeToTilde(char* path,char* homedir);

void subTildetoHome(char* path,char* homedir);

int splitArgs(char** argv,char* command,char** inputFile,char** outputFile);