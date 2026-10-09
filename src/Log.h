#pragma once
#include <iostream>
#include <stdarg.h>

static class Log
{
private:

public:
    void Warn(const char *msg, char *extra = nullptr);
    void FatalError(const char *msg, char *extra = nullptr);

} Log;