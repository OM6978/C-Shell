#pragma once

#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

static const char* LOG_FILE = "/home/om/Acads/C-Shell/log.txt";

void logInit();

void logMessage(const char *format, ...);

void logArgs(char ** argv);

void logDest();