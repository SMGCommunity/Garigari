#pragma once

#include <revolution.h>

class JMapInfoIter;

namespace MR {
    bool getJMapInfoGroupID(const JMapInfoIter &, s32 *);

    bool isConnectedWithRail(const JMapInfoIter &);
};
