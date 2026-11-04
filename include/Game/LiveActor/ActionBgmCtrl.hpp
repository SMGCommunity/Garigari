#pragma once

#include <revolution/types.h>

class ModelManager;

struct ActionBgmInfo {
    ActionBgmInfo();

    /* 0x00 */ const char* mBckName;
    /* 0x04 */ f32 mBckStartFrame;
    /* 0x08 */ const char* mBgmName;
    /* 0x0C */ s32 mBgmStateNo;
    /* 0x10 */ bool mIsBgmStopped;
    /* 0x14 */ s32 mBgmFadeStep;
    /* 0x18 */ const char* mStageName;
    /* 0x1C */ s32 mStageScenarioNo;
    /* 0x20 */ bool mIsPlaying;
    /* 0x21 */ bool mIsUpdated;
};

class ActionBgmCtrl {
public:
    ActionBgmCtrl(const ModelManager*);

    static ActionBgmCtrl* tryCreate(const ModelManager*);
    
    void update();
    void findAndUpdateBgm();
    void updateBgm(ActionBgmInfo*);

    /* 0x0 */ const ModelManager* mModelManager;
    /* 0x4 */ const char* mPlayingBckName;
    /* 0x8 */ s32 mBgmInfoCount;
    /* 0xC */ ActionBgmInfo* mBgmInfos;
};
