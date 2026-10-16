#pragma once
#include <iostream>
#include <stdarg.h>

extern class Log
{
private:

public:
    void Warn(const char *msg, char *extra = nullptr);
    void FatalError(const char *msg, char *extra = nullptr);

    void ResetPerFrameCounters();
    void PrintCounters();

    int countVAOBinds;
    int countUniforms;
    int countDraws;


} logger;