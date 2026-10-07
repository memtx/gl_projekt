#include "Log.h"

void Log::Warn(const char *msg, char *extra)
{
    if(extra == nullptr)
        printf("WARNING: %s (%s)\n", msg, "");
    else
        printf("WARNING: %s (%s)\n", msg, extra);

}

void Log::Error(const char *msg, char *extra)
{
    if(extra == nullptr)
        printf("ERROR: %s (%s)\n", msg, "");
    else
        printf("ERROR: %s (%s)\n", msg, extra);
        
    exit(-1);
}