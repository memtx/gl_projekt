#include "Log.h"

void Log::Warn(const char *msg)
{
    printf(" (Warning) %s\n", msg);
}

void Log::Error(const char *msg)
{
    printf("ERROR: %s\n", msg);
    exit(-1);
}