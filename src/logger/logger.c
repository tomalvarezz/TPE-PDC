// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "logger.h"
#include "socks_utils.h"
#include <stdio.h>
#include <time.h>

#define MAX_DATE 21

static char* get_date();

LOG_LEVEL current_level = DEBUG;

static char* get_date() {
    char date[MAX_DATE];
    time_t now = time(NULL);
    struct tm* time_info = localtime(&now);
    strftime(date, MAX_DATE, "%FT%TZ", time_info);
    return date;
}

void setLogLevel(LOG_LEVEL newLevel) {
    if (newLevel >= DEBUG && newLevel <= FATAL)
        current_level = newLevel;
}

char* levelDescription(LOG_LEVEL level) {
    static char* description[] = {"DEBUG", "INFO", "ERROR", "FATAL"};
    if (level < DEBUG || level > FATAL)
        return "";
    return description[level];
}

void logger(LOG_LEVEL level, const char* fmt, ...) {
    if (level >= current_level) {
        fprintf(stderr, "%s: ", levelDescription(level));
        va_list arg;
        va_start(arg, fmt);
        vfprintf(stderr, fmt, arg);
        va_end(arg);
        fprintf(stderr, "\n");
    }
    if (level == FATAL)
        exit(1);
}

void sniffer_logger(char* username, char* password) {
    logger(INFO, "%s\t Sniffed credentials: %s:%s\n", get_date(), username, password);
}
