#include "Log.h"

Log logger;

void Log::Warn(const char *msg, char *extra)
{
    if(extra == nullptr)
        printf("WARNING: %s (%s)\n", msg, "");
    else
        printf("WARNING: %s (%s)\n", msg, extra);

}

void Log::FatalError(const char *msg, char *extra)
{
    if(extra == nullptr)
        printf("ERROR: %s (%s)\n", msg, "");
    else
        printf("ERROR: %s (%s)\n", msg, extra);
        
    exit(-1);
}

void Log::ResetPerFrameCounters()
{
    countVAOBinds = 0; 
    countUniforms = 0; 
    countDraws = 0;
    countOptionalUniforms = 0;
    countShaderUses = 0;
}

void Log::PrintCounters()
{
    printf("VAO:%d, Uniform:%d, Draw:%d, MaterialUniforms: %d, ShaderUses: %d\n", countVAOBinds, countUniforms, countDraws, countOptionalUniforms, countShaderUses);
}