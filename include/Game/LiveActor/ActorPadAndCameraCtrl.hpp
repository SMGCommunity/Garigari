#pragma once

#include <JSystem/JGeometry/TVec.hpp>

class ModelManager;
class ResourceHolder;

struct ActorPadAndCameraInfo {
    /* 0x00 */ const char* mBckName;
    /* 0x04 */ f32 mStartFrame;
    /* 0x08 */ f32 mEndFrame;
    /* 0x0C */ const char* mPadRumbleName;
    /* 0x10 */ const char* mCameraShakeName;
    /* 0x14 */ const char* mPadRumbleNameMiddle;
    /* 0x18 */ const char* mCameraShakeNameMiddle;
    /* 0x1C */ const char* mPadRumbleNameFar;
    /* 0x20 */ const char* mCameraShakeNameFar;
    /* 0x24 */ f32 mDistanceNear;
    /* 0x28 */ f32 mDistanceFar;
    /* 0x2C */ f32 mDistanceInvalid;
    /* 0x30 */ bool mIsPlaying;
    /* 0x31 */ bool mIsActive;
};

class ActorPadAndCameraCtrl {
public:
    ActorPadAndCameraCtrl(const ModelManager*, const TVec3f*);

    static ActorPadAndCameraCtrl* tryCreate(const ModelManager*, const TVec3f*);

    void update();
    void updateInfoBck();
    void updatePadAndCamera(const ActorPadAndCameraInfo*);

    /* 0x00 */ const ModelManager* mModelManager;
    /* 0x04 */ const TVec3f* _4;
    /* 0x08 */ ResourceHolder* mResourceHolder;
    /* 0x0C */ const char* mPlayingBckName;
    /* 0x10 */ s32 mInfoCount;
    /* 0x14 */ ActorPadAndCameraInfo* mInfos;
};
