#include "Log.h"

void Log::Warn(char *msg)
{
    printf(" (Warning) %s\n", msg);
}

void Log::Error(char *msg)
{
    printf("ERROR: %s\n", msg);
    exit(-1);
}