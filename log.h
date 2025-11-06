#pragma once

#include <stdio.h>
#include <time.h>
#include <stdarg.h>

static const char* LOG_FILE = "/home/om/Acads/C-Shell/log.txt";

void logInit();

void logString(int num_args, ...);

void logInteger(int x);

void logDest();