#pragma once

#include "Game/LiveActor/LiveActor.hpp"

#include <revolution/mtx.h>

class FileSelectModel : LiveActor {
public:
    FileSelectModel(const char*, MtxPtr, const char*);

    ~FileSelectModel();

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
    void exeBlinkOnce();
    void exeBlink();
    void calcAndSetBaseMtx();

    void exeOpen();
    void exeClose();

    /* 0x90 */ MtxPtr _90;
};
