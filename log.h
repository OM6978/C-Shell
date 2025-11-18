#pragma once

#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

extern char logPath[PATH_MAX];

void logInit();

void logMessage(const char *format, ...);

void logArgs(char ** argv);

void logDest();