#pragma once

#include <revolution.h>
#include <JGeometry.hpp>

class JMapInfoIter;

namespace MR {
    bool getJMapInfoGroupID(const JMapInfoIter &, s32 *);

    bool isConnectedWithRail(const JMapInfoIter &);

    void getObjectName(const char **, const JMapInfoIter &);

    void getJMapInfoTrans(const JMapInfoIter &, TVec3f *);
    void getJMapInfoRotate(const JMapInfoIter &, TVec3f *);
    void getJMapInfoScale(const JMapInfoIter &, TVec3f *);
};
