#ifndef GSystem_h
#define GSystem_h


#include "GXPrefix.h"

class GSystem
{
public:
    static gint64 currentTimeMS();
    static gint64 tickCountNS();
};

#endif