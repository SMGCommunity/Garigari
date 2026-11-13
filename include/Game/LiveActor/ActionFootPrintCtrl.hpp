#pragma once

#include <revolution/types.h>

class LiveActor;
class FootPrint;

struct ActionFootPrintInfo {
    ActionFootPrintInfo();

    /* 0x0 */ const char* mBckName;
    /* 0x4 */ f32 mBckStartFrame;
    /* 0x8 */ const char* mJointName;
    /* 0xC */ bool mIsRight;
    /* 0xD */ bool mIsPlaying;
};

class ActionFootPrintCtrl {
public:
    ActionFootPrintCtrl(LiveActor*);

    static ActionFootPrintCtrl* tryCreate(LiveActor*);

    void update();
    void findAndUpdateFootPrint();

    /* 0x00 */ LiveActor* mHost;
    /* 0x04 */ const char* mPlayingBckName;
    /* 0x08 */ FootPrint* mFootPrint;
    /* 0x0C */ s32 mFootPrintInfoCount;
    /* 0x10 */ ActionFootPrintInfo* mFootPrintInfos;
};
