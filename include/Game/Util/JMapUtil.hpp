#pragma once

#include <revolution.h>
#include <JGeometry.hpp>

class JMapInfoIter;

namespace MR {
    bool getJMapInfoGroupID(const JMapInfoIter &, s32 *);

    bool isConnectedWithRail(const JMapInfoIter &);
    bool isExistStageSwitchA(const JMapInfoIter &);
    bool isExistStageSwitchB(const JMapInfoIter &);
    bool isExistStageSwitchAppear(const JMapInfoIter &);
    bool isExistStageSwitchDead(const JMapInfoIter &);
    bool isExistStageSwitchAwake(const JMapInfoIter &);
    bool isExistStageSwitchParam(const JMapInfoIter &);
    bool isExistMessageId(const JMapInfoIter &);
    bool isEqualObjectName(const JMapInfoIter &, const char *);
    bool getJMapInfoCameraSetID(const JMapInfoIter &, s32 *);
    bool getJMapInfoViewGroupID(const JMapInfoIter &, s32 *);
    bool getJMapInfoMessageID(const JMapInfoIter &, s32 *);

    void getObjectName(const char **, const JMapInfoIter &);

    void getJMapInfoTrans(const JMapInfoIter &, TVec3f *);
    void getJMapInfoRotate(const JMapInfoIter &, TVec3f *);
    void getJMapInfoScale(const JMapInfoIter &, TVec3f *);
};
