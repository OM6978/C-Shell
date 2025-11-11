#pragma once

#include "includes.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define PATH_MAX 1000
#define H_NAME_MAX 1000
#define COMMAND_MAX 1000
#define HISTORY_LEN 20
#define HISTORY_DISPLAY 10
#define MAX_ARGS 64

#define DELIMITERS " \t\n"

#define LIME_GREEN "\033[38;2;134;252;121m"
#define NORD_BLUE "\033[38;2;129;161;193m"
#define LIGHT_BLUE "\033[38;2;136;192;208m"
#define REG_BLUE "\033[38;2;41;183;219m"

#define BOLD_LIGHT_GREEN "\033[1;38;2;101;252;101m"
#define BOLD_BLUE "\033[1;38;2;41;183;219m"
#define BOLD_LIME_GREEN "\033[1;38;2;134;252;121m"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"