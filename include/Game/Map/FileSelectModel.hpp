#pragma once

#include "Game/LiveActor/LiveActor.hpp"
#include <revolution/mtx.h>

class FileSelectModel : public LiveActor {
public:
    FileSelectModel(const char*, MtxPtr, const char*);

    void calcAnim();
    void open();
    void blinkOnce();
    void close();
    void blink();
    bool isOpen() const;
    void emitOpen();
    void emitVanish();
    void emitCopy();
    void emitCompleteEffect();
    void deleteCompleteEffect();
    void exeOpen();
    void exeBlinkOnce();
    void exeBlink();
    void exeClose();
    void calcAndSetBaseMtx();

    /* 0x90 */ MtxPtr _90;
};
